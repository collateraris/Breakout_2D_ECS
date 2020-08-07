#include <PlayerBallLogicSystem.h>

#include <EntityComponentSystem.h>
#include <PlayerBallComponent.h>
#include <PlayerComponent.h>
#include <ColliderComponent.h>

#include <EventsStorage.h>

#include <gameContext.h>
#include <gameWindow.h>
#include <components/TransformComponent.h>
#include <MovementComponent.h>

#include <algorithm>

using namespace breakout;

void PlayerBallLogicSystem::Init()
{

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

	const auto& ballSize = ballTransform.GetScale();
	auto& colliderComponent = GameContext::Get().GetECS().GetComponentByEntityId<ColliderComponent>(m_playerBallEntityId);
	colliderComponent.SetCenter(ballPos[0] + ballSize[0] * 0.5f, ballPos[1] + ballSize[1] * 0.5f);
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
}


