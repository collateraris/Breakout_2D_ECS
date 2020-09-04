#include <PlayerBallLogicSystem.h>

#include <EntityComponentSystem.h>
#include <PlayerBallComponent.h>
#include <PlayerComponent.h>
#include <ColliderComponent.h>
#include <HealthComponent.h>
#include <CollisionSystem.h>
#include <AudioManager.h>

#include <EventsStorage.h>
#include <GameStateManager.h>

#include <gameContext.h>
#include <components/TransformComponent.h>
#include <MovementComponent.h>
#include <ParticlesComponent.h>

#include <EventManager.h>
#include <ECSBreakout.h>
#include <GameMaps.h>
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
	auto& eventManager = EventManager::Get();

	eventManager.OnCollitionDetected().BindObject(this, &PlayerBallLogicSystem::CollitionResolution);
	eventManager.OnNewLevelLoaded().BindObject(this, &PlayerBallLogicSystem::SetInitLevelBlocks);
	eventManager.OnGameEnded().BindObject(this, &PlayerBallLogicSystem::Restart);
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
	case EPlayerBallState::Sticky:
		MoveLogic(dtMilliseconds);
		break;
	default:
		break;
	}

	BallParticlesShow();
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
	const auto& initVelocity = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::playerBallVelocity)];
	newVelocity.x() = initVelocity[0] * percentage * strength;
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
		float penetration = ballRadius - std::abs(difference.x());
		ballPos.x() += bestDir == EDirection::LEFT ? penetration : -penetration;
	}
	else // vertical collision
	{
		ballVelocity.y() *= -1.0f;
		float penetration = ballRadius - std::abs(difference.y());
		ballPos.y() += bestDir == EDirection::UP ? -penetration : penetration;
	}

	ballMovement.SetVelocity(ballVelocity.data());
	ballTransform.SetPosition(ballPos.data());


}

void PlayerBallLogicSystem::CollitionResolution(const ColliderComponent& componentA, const ColliderComponent& componentB)
{
	auto& ecs = EntityComponentSystem::Get();
	if (!ecs.IsExistEntityId(componentA.m_entityId) || !ecs.IsExistEntityId(componentB.m_entityId))
		return;

	const ColliderComponent* playerBall = nullptr;
	const ColliderComponent* Block = nullptr;
	const ColliderComponent* Player = nullptr;

	auto FindPlayerBall = [&](const ColliderComponent& candidate)
	{
		if (ecs.IsSameEntityType(static_cast<int>(EEntityType::PlayerBall), candidate.m_entityId))
		{
			playerBall = &candidate;
		}
	};

	auto FindBlock = [&](const ColliderComponent& candidate)
	{
		if (ecs.IsSameEntityType(static_cast<int>(EEntityType::Block), candidate.m_entityId)
			|| ecs.IsSameEntityType(static_cast<int>(EEntityType::SolidBlock), candidate.m_entityId))
		{
			Block = &candidate;
		}
	};

	auto FindPlayer = [&](const ColliderComponent& candidate)
	{
		if (ecs.IsSameEntityType(static_cast<int>(EEntityType::PlayerPaddle), candidate.m_entityId))
		{
			Player = &candidate;
		}
	};

	FindBlock(componentA);
	FindPlayer(componentA);
	FindPlayerBall(componentA);

	FindBlock(componentB);
	FindPlayer(componentB);
	FindPlayerBall(componentB);

	if (playerBall && playerBall->GetDamagableType() == EDamagableType::Intacted)
	{
		return;
	}

	if (playerBall && Player)
	{
		EPlayerBallState& ballState = EntityComponentSystem::Get().GetComponentByEntityId<PlayerBallComponent>(playerBall->m_entityId).state;
		if (ballState == EPlayerBallState::Sticky)
		{
			SetInitPosition();
			ballState = EPlayerBallState::IsStuckOnPlayerPaddle;
		}
		else if (ballState != EPlayerBallState::IsStuckOnPlayerPaddle)
		{
			AudioManager::Get().PlaySound(ESoundAssetId::PaddlePass);
			PaddlePlayerCollition(*playerBall, *Player);
		}
	}
	else if (playerBall && Block)
	{
		BlockCollition(*playerBall, *Block);

		if (Block->GetDamagableType() == EDamagableType::Saved)
		{
			AudioManager::Get().PlaySound(ESoundAssetId::HitSolidBlock);
		}
		else if (Block->GetDamagableType() == EDamagableType::Destroyable)
		{
			AudioManager::Get().PlaySound(ESoundAssetId::HitNonSolidBlock);
			TryWin();
		}
	}
}

void PlayerBallLogicSystem::SetPlayerEntityId()
{
	m_playerEntityId = ECSBreakout::GetInitGameData().playerId;
}

void PlayerBallLogicSystem::SetPlayerBallEntityId()
{
	m_playerBallEntityId = ECSBreakout::GetInitGameData().playerBallId;
}

void PlayerBallLogicSystem::SetInitLevelBlocks()
{
	m_levelBlocksNum = GameMaps::Get().GetBlockNum();
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
	Vector2<float> deltaPos({playerSize[0] * 0.5f - ballRadius * 0.5f, - playerSize[1] - ballRadius * 0.25f });
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

	int w, h;
	GameContext::Get().GetMainWindowSize(w, h);
	float screenWidth = static_cast<float>(w), 
		screeHeight = static_cast<float>(h);

	if (ballPos.x() <= 0.0f)
	{
		ballMovement.SetVelocity({-ballVelocity.x(), ballVelocity.y() });
		ballPos.x() = 0.f;
	}
	else if (ballPos.x() + ballSize.x() >= screenWidth)
	{
		ballMovement.SetVelocity({ -ballVelocity.x(), ballVelocity.y() });
		ballPos = { screenWidth - ballSize.x(), ballPos.y() };
	}
	if (ballPos.y() <= 0.0f)
	{
		ballMovement.SetVelocity({ ballVelocity.x(), -ballVelocity.y() });
		ballPos.y() = 0.f;
	}
	else if (ballPos.y() + ballSize.y() >= 1.25 * screeHeight)
	{
		SetInitPosition();
		EntityComponentSystem::Get().GetComponentByEntityId<PlayerBallComponent>(m_playerBallEntityId).state = EPlayerBallState::IsStuckOnPlayerPaddle;

		LossHealth();
		return;
	}


	ballTransform.SetPosition(ballPos.data());

	auto& colliderComponent = GameContext::Get().GetECS().GetComponentByEntityId<ColliderComponent>(m_playerBallEntityId);
	colliderComponent.SetPosition(ballPos.data());
}

void PlayerBallLogicSystem::BallParticlesShow()
{
	auto& ballTransform = GameContext::Get().GetECS().GetComponentByEntityId<TransformComponent>(m_playerBallEntityId);
	Vector2<float> ballSize = ballTransform.GetScale();
	GameContext::Get().GetECS().GetComponentByEntityId<ParticlesComponent>(m_playerBallEntityId).RespawnParticle(2, (ballSize * 0.5).data());
}

void PlayerBallLogicSystem::LossHealth()
{
	auto& health = GameContext::Get().GetECS().GetComponentByEntityId<HealthComponent>(m_playerEntityId);
	health.LossHealth(1);

	if (health.IsDead())
	{
		GameStateManager::Get().SwitchState(EGameState::GAME_OVER);
	}
}

void PlayerBallLogicSystem::LossLevelBlock()
{
	m_levelBlocksNum--;
}

void PlayerBallLogicSystem::TryWin()
{
	LossLevelBlock();

	if (m_levelBlocksNum <= 0)
	{
		GameStateManager::Get().SwitchState(EGameState::GAME_WIN);
	}
}

void PlayerBallLogicSystem::Restart()
{
	auto& health = GameContext::Get().GetECS().GetComponentByEntityId<HealthComponent>(m_playerEntityId);
	health.SetHealth(ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::playerLives)][0]);

	SetInitPosition();
	EntityComponentSystem::Get().GetComponentByEntityId<PlayerBallComponent>(m_playerBallEntityId).state = EPlayerBallState::IsStuckOnPlayerPaddle;
}

