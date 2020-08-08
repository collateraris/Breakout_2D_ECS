#include <PlayerBallLogicSystem.h>

#include <EntityComponentSystem.h>
#include <PlayerBallComponent.h>
#include <PlayerComponent.h>
#include <ColliderComponent.h>
#include <CollisionSystem.h>

#include <EventsStorage.h>

#include <gameContext.h>
#include <gameWindow.h>
#include <components/TransformComponent.h>
#include <MovementComponent.h>

#include <EventManager.h>
#include <Vector2.h>

#include <algorithm>
#include <numeric>
#include <cassert>


using namespace breakout;

enum class EDirection
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

void PlayerBallLogicSystem::Init()
{
	EventManager::Get().OnCollitionDetected().BindObject(this, &PlayerBallLogicSystem::CollitionResolution);
}

void PlayerBallLogicSystem::Update(float dtMilliseconds)
{
	if (m_playerEntityId == -1)
	{
		SetPlayerEntityId();
		SetPlayerBallEntityId();
		SetInitPosition();
	}

	EPlayerBallState ballState = EntityComponentSystem::Get().GetComponentByEntityId<PlayerBallComponent>(m_playerBallEntityId).state;

	switch (ballState)
	{
	case EPlayerBallState::IsStuckOnPlayerPaddle:
		IsStuckOnPlayerPaddleLogic(dtMilliseconds);
		break;
	case EPlayerBallState::Move:
		MoveLogic(dtMilliseconds);
		break;
	default:
		break;
	}
}

void PlayerBallLogicSystem::PaddlePlayerCollition(const ColliderComponent& ballCollider, const ColliderComponent& playerCollider) const
{
	Vector2<float> ballPos = ballCollider.GetPosition();
	float ballRadius = ballCollider.GetRadius();
	Vector2<float> paddlePos = playerCollider.GetPosition();
	float paddleWidth = playerCollider.GetWidth();

	float centerBoard = paddlePos.x() + paddleWidth * 0.5f;
	float distance = (ballPos.x() + ballRadius) - centerBoard;
	float percentage = distance * (2.f / paddleWidth);
	float strength = 2.f;

	auto& ballMovement = EntityComponentSystem::Get().GetComponentByEntityId<MovementComponent>(ballCollider.m_entityId);
	Vector2<float> oldVelocity = ballMovement.GetVelocity();
	Vector2<float> newVelocity = ballMovement.GetVelocity();
	newVelocity.x() = m_ballInitVelocity[0] * percentage * strength;
	newVelocity = newVelocity.normalized() * oldVelocity.length();
	newVelocity.y() = -1.0f * abs(newVelocity.y());
	ballMovement.SetVelocity(newVelocity.data());
}

void PlayerBallLogicSystem::BlockCollition(const ColliderComponent& circleCollider, const ColliderComponent& squareCollider) const
{
	std::array<std::array<float, 2>, 4> directions = { {{0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, -1.0f}, {-1.0f, 0.0f}} };
	Vector2<float> difference = CollisionSystem::GetCircle_AABBCollisionDiff(circleCollider, squareCollider);
	difference = difference.normalized();

	float maxDotProduct = 0.f;
	EDirection bestDir = EDirection::UP;
	for (int i = 0; i < directions.size(); ++i)
	{
		float dotProduct = Vector2<float>::Dot(difference.data(), directions[i]);
		if (dotProduct > maxDotProduct)
		{
			maxDotProduct = dotProduct;
			bestDir = static_cast<EDirection>(i);
		}
	}
	auto& ballMovement = EntityComponentSystem::Get()
		.GetComponentByEntityId<MovementComponent>(circleCollider.m_entityId);

	auto& ballTransform = EntityComponentSystem::Get()
		.GetComponentByEntityId<TransformComponent>(circleCollider.m_entityId);

	Vector2<float> ballVelocity = ballMovement.GetVelocity();
	Vector2<float> ballPos = ballTransform.GetPosition();
	float ballRadius = circleCollider.GetRadius();

	if (bestDir == EDirection::LEFT || bestDir == EDirection::RIGHT) // horizontal collision
	{
		ballVelocity.x() *= -1.0f;
		float penetration = ballRadius - std::abs(difference[0]);
		ballPos.x() += bestDir == EDirection::LEFT ? penetration : -penetration;
	}
	else // vertical collision
	{
		ballVelocity.y() *= -1.0f;
		float penetration = ballRadius - std::abs(difference[1]);
		ballPos.y() += bestDir == EDirection::UP ? penetration : -penetration;
	}

	ballMovement.SetVelocity(ballVelocity.data());

	auto IsPlayer = [&](const ColliderComponent& component) -> bool
	{
		return component.m_entityId == m_playerEntityId;
	};

	ballTransform.SetPosition(ballPos.data());

	if (IsPlayer(squareCollider))
	{
		PaddlePlayerCollition(circleCollider, squareCollider);
	}
}

void PlayerBallLogicSystem::CollitionResolution(const ColliderComponent& componentA, const ColliderComponent& componentB)
{
	const auto& circleCollider = componentA.GetColliderType() == EColliderType::Circle ? componentA : componentB;
	const auto& squareCollider = componentB.GetColliderType() == EColliderType::Square ? componentB : componentA;
	if (circleCollider.GetColliderType() != EColliderType::Circle || squareCollider.GetColliderType() != EColliderType::Square)
		return;

	BlockCollition(circleCollider, squareCollider);	
}

void PlayerBallLogicSystem::SetPlayerEntityId()
{
	auto& playerComponents = EntityComponentSystem::Get().GetAllComponentsByType<PlayerComponent>();

	for (auto& player : playerComponents)
	{
		m_playerEntityId = player->GetContainer().m_entityId;
		break;
	}
}

void PlayerBallLogicSystem::SetPlayerBallEntityId()
{
	auto& ballComponents = EntityComponentSystem::Get().GetAllComponentsByType<PlayerBallComponent>();

	for (auto& ball : ballComponents)
	{
		m_playerBallEntityId = ball->GetContainer().m_entityId;
		break;
	}
}

void PlayerBallLogicSystem::IsStuckOnPlayerPaddleLogic(float dtMilliseconds)
{
	if (EventsStorage::Get().IsContain(EEventType::PLAYER_ACTION_MOVE_LEFT))
	{
		auto& actions = EventsStorage::Get().GetAll(EEventType::PLAYER_ACTION_MOVE_LEFT);
		for (auto& action : actions)
		{
			PlayerMoveLeftAction(dtMilliseconds);
		}
	}

	if (EventsStorage::Get().IsContain(EEventType::PLAYER_ACTION_MOVE_RIGHT))
	{
		auto& actions = EventsStorage::Get().GetAll(EEventType::PLAYER_ACTION_MOVE_RIGHT);
		for (auto& action : actions)
		{
			PlayerMoveRightAction(dtMilliseconds);
		}
	}

	if (EventsStorage::Get().IsContain(EEventType::PLAYER_ACTION_SPACE_CLICK))
	{
		PlayerSpaceClickAction(dtMilliseconds);
	}
}

void PlayerBallLogicSystem::PlayerSpaceClickAction(float dtMilliseconds)
{
	auto& ball = GameContext::Get().GetECS().GetComponentByEntityId<PlayerBallComponent>(m_playerBallEntityId);
	ball.state = EPlayerBallState::Move;
}

void PlayerBallLogicSystem::PlayerMoveLeftAction(float dtMilliseconds)
{
	SetPosition(false, -1, dtMilliseconds);
}

void PlayerBallLogicSystem::PlayerMoveRightAction(float dtMilliseconds)
{
	SetPosition(false, 1, dtMilliseconds);
}

void PlayerBallLogicSystem::SetInitPosition()
{
	SetPosition(false, 1, 0.f);
}

void PlayerBallLogicSystem::SetPosition(bool axis /* false - x, true - y*/, short int velocitySign /* <0 - negative, >= - positive*/, float dtMilliseconds)
{
	auto& playerTransform = GameContext::Get().GetECS().GetComponentByEntityId<TransformComponent>(m_playerEntityId);
	Vector2<float> playerPos = playerTransform.GetPosition();
		
	auto& ballTransform = GameContext::Get().GetECS().GetComponentByEntityId<TransformComponent>(m_playerBallEntityId);
	const auto& playerSize = playerTransform.GetScale();
	float ballRadius = ballTransform.GetScale()[axis];
	Vector2<float> deltaPos({playerSize[0] * 0.5f - ballRadius * 2.0f, -ballRadius * 2.0f});
	Vector2<float> ballPos = playerPos + deltaPos;

	auto& playerMovement = GameContext::Get().GetECS().GetComponentByEntityId<MovementComponent>(m_playerEntityId);
	auto playerVelocity = playerMovement.GetVelocity()[axis] * dtMilliseconds;
	int sign = velocitySign < 0 ? -1 : 1;
	ballPos.x() += velocitySign * playerVelocity * dtMilliseconds;
	ballTransform.SetPosition(ballPos.data());

	auto& colliderComponent = GameContext::Get().GetECS().GetComponentByEntityId<ColliderComponent>(m_playerBallEntityId);
	colliderComponent.SetPosition(ballPos.data());
}

void PlayerBallLogicSystem::MoveLogic(float dtMilliseconds)
{
	auto& ballTransform = GameContext::Get().GetECS().GetComponentByEntityId<TransformComponent>(m_playerBallEntityId);
	Vector2<float> ballPos = ballTransform.GetPosition();
	Vector2<float> ballSize = ballTransform.GetScale();

	auto& ballMovement = GameContext::Get().GetECS().GetComponentByEntityId<MovementComponent>(m_playerBallEntityId);
	Vector2<float> ballVelocity = ballMovement.GetVelocity();
	ballPos += ballVelocity * dtMilliseconds;

	auto window = GameContext::Get().GetMainWindow();
	float screenWidth = window->GetWidth();

	if (ballPos.x() <= 0.0f)
	{
		ballMovement.SetVelocity({-ballVelocity.x(), -ballVelocity.y() });
		ballPos.x() = 0.f;
	}
	else if (ballPos.x() + ballSize.x() >= screenWidth)
	{
		ballMovement.SetVelocity({ -ballVelocity.x(), -ballVelocity.y() });
		ballPos = { screenWidth - ballSize.x(), ballPos.y() };
	}
	if (ballPos.y() <= 0.0f)
	{
		ballMovement.SetVelocity({ -ballVelocity.x(), -ballVelocity.y() });
		ballPos.y() = 0.f;
	}

	ballTransform.SetPosition(ballPos.data());

	auto& colliderComponent = GameContext::Get().GetECS().GetComponentByEntityId<ColliderComponent>(m_playerBallEntityId);
	colliderComponent.SetPosition(ballPos.data());
}


