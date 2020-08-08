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

void PlayerBallLogicSystem::CollitionResolution(const ColliderComponent& componentA, const ColliderComponent& componentB)
{
	const auto& circleCollider = componentA.GetColliderType() == EColliderType::Circle ? componentA : componentB;
	const auto& squareCollider = componentB.GetColliderType() == EColliderType::Square ? componentB : componentA;
	if (circleCollider.GetColliderType() != EColliderType::Circle || squareCollider.GetColliderType() != EColliderType::Square)
		return;


	std::array<std::array<float, 2>, 4> directions = { {{0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, -1.0f}, {-1.0f, 0.0f}} };
	std::array<float, 2> difference = CollisionSystem::GetCircle_AABBCollisionDiff(circleCollider, squareCollider);
	float invDifferenceLen = 1.0f / sqrtf(difference[0] * difference[0] + difference[1] * difference[1]);
	difference = { difference[0] * invDifferenceLen, difference[1] * invDifferenceLen };

	float maxDotProduct = 0.f;
	EDirection bestDir = EDirection::UP;
	for(int i = 0; i < directions.size(); ++i)
	{
		float dotProduct = std::inner_product(difference.begin(), difference.end(), directions[i].begin(), 0);
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

	std::array<float, 2> ballVelocity = ballMovement.GetVelocity();
	std::array<float, 2> ballPos = ballTransform.GetPosition();
	float ballRadius = circleCollider.GetRadius();

	if (bestDir == EDirection::LEFT || bestDir == EDirection::RIGHT) // horizontal collision
	{
		ballVelocity[0] *= -1.0f;
		float penetration = ballRadius - std::abs(difference[0]);
		ballPos[0] += bestDir == EDirection::LEFT ? penetration : -penetration;
	}
	else // vertical collision
	{
		ballVelocity[1] *= -1.0f;
		float penetration = ballRadius - std::abs(difference[1]);
		ballPos[1] += bestDir == EDirection::UP ? penetration : -penetration;
	}

	ballMovement.SetVelocity(ballVelocity);
	ballTransform.SetPosition(ballPos);
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
	const auto& playerPos = playerTransform.GetPosition();
		
	auto& ballTransform = GameContext::Get().GetECS().GetComponentByEntityId<TransformComponent>(m_playerBallEntityId);
	const auto& playerSize = playerTransform.GetScale();
	float ballRadius = ballTransform.GetScale()[axis];
	const std::array<float, 2> deltaPos = {playerSize[0] * 0.5f - ballRadius * 2.0f, -ballRadius * 2.0f};
	std::array<float, 2> ballPos = {playerPos[0] + deltaPos[0], playerPos[1] + deltaPos[1] };

	auto& playerMovement = GameContext::Get().GetECS().GetComponentByEntityId<MovementComponent>(m_playerEntityId);
	auto playerVelocity = playerMovement.GetVelocity()[axis] * dtMilliseconds;
	int sign = velocitySign < 0 ? -1 : 1;
	ballPos[axis] += velocitySign * playerVelocity * dtMilliseconds;
	ballTransform.SetPosition(ballPos);

	auto& colliderComponent = GameContext::Get().GetECS().GetComponentByEntityId<ColliderComponent>(m_playerBallEntityId);
	colliderComponent.SetPosition(ballPos);
}

void PlayerBallLogicSystem::MoveLogic(float dtMilliseconds)
{
	auto& ballTransform = GameContext::Get().GetECS().GetComponentByEntityId<TransformComponent>(m_playerBallEntityId);
	auto ballPos = ballTransform.GetPosition();
	const auto& ballSize = ballTransform.GetScale();

	auto& ballMovement = GameContext::Get().GetECS().GetComponentByEntityId<MovementComponent>(m_playerBallEntityId);
	const auto& ballVelocity = ballMovement.GetVelocity();
	ballPos = { ballPos[0] + ballVelocity[0] * dtMilliseconds, ballPos[1] + ballVelocity[1] * dtMilliseconds };

	auto window = GameContext::Get().GetMainWindow();
	float screenWidth = window->GetWidth();

	if (ballPos[0] <= 0.0f)
	{
		ballMovement.SetVelocity({-ballVelocity[0], -ballVelocity[1] });
		ballPos = {0.f, ballPos[1] };
	}
	else if (ballPos[0] + ballSize[0] >= screenWidth)
	{
		ballMovement.SetVelocity({ -ballVelocity[0], -ballVelocity[1] });
		ballPos = { screenWidth - ballSize[0], ballPos[1] };
	}
	if (ballPos[1] <= 0.0f)
	{
		ballMovement.SetVelocity({ -ballVelocity[0], -ballVelocity[1] });
		ballPos = { ballPos[0], 0.f };
	}

	ballTransform.SetPosition(ballPos);

	auto& colliderComponent = GameContext::Get().GetECS().GetComponentByEntityId<ColliderComponent>(m_playerBallEntityId);
	colliderComponent.SetPosition(ballPos);
}


