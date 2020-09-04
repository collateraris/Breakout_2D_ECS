#include <PlayerLogicSystem.h>

#include <EntityComponentSystem.h>
#include <PlayerComponent.h>
#include <ColliderComponent.h>

#include <EventsStorage.h>
#include <InputManager.h>
#include <EventManager.h>
#include <ECSBreakout.h>

#include <gameContext.h>
#include <gameWindow.h>
#include <components/TransformComponent.h>
#include <MovementComponent.h>

#include <algorithm>

using namespace breakout;

void PlayerLogicSystem::Init()
{
	InputManager::Get().OnKeyPressed().BindLambda([&](oglml::EKeyButtonCode key, oglml::EKeyModeCode mode)
	{
		if (key == oglml::EKeyButtonCode::KEY_A)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_MOVE_LEFT));
		}
		else if (key == oglml::EKeyButtonCode::KEY_D)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_MOVE_RIGHT));
		}
		else if (key == oglml::EKeyButtonCode::KEY_SPACE)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_SPACE_CLICK));
		}
	});

	EventManager::Get().OnGameEnded().BindObject(this, &PlayerLogicSystem::Restart);
}

void PlayerLogicSystem::Update(float dtMilliseconds)
{
	if (m_playerEntityId == -1)
		SetPlayerEntityId();

	if (EventsStorage::Get().IsContain(EEventType::PLAYER_ACTION_MOVE_LEFT))
	{
		auto& actions = EventsStorage::Get().GetAll(EEventType::PLAYER_ACTION_MOVE_LEFT);
		for (auto& action : actions)
		{
			MoveLeftAction(dtMilliseconds);
		}
	}

	if (EventsStorage::Get().IsContain(EEventType::PLAYER_ACTION_MOVE_RIGHT))
	{
		auto& actions = EventsStorage::Get().GetAll(EEventType::PLAYER_ACTION_MOVE_RIGHT);
		for (auto& action : actions)
		{
			MoveRightAction(dtMilliseconds);
		}
	}
}

void PlayerLogicSystem::SetPlayerEntityId()
{
	m_playerEntityId = ECSBreakout::GetInitGameData().playerId;
}

void PlayerLogicSystem::MoveLeftAction(float dtMilliseconds)
{
	SetPosition(false, -1, dtMilliseconds);
}

void PlayerLogicSystem::MoveRightAction(float dtMilliseconds)
{
	SetPosition(false, 1, dtMilliseconds);
}

void PlayerLogicSystem::SetPosition(bool axis /* false - x, true - y*/, short int velocitySign /* <0 - negative, >= - positive*/, float dtMilliseconds)
{
	auto& transformComponent = GameContext::Get().GetECS().GetComponentByEntityId<TransformComponent>(m_playerEntityId);
	auto pos = transformComponent.GetPosition();
	auto& movementComponent = GameContext::Get().GetECS().GetComponentByEntityId<MovementComponent>(m_playerEntityId);
	auto velocity = movementComponent.GetVelocity()[axis] * dtMilliseconds;
	int sign = velocitySign < 0 ? -1 : 1;
	pos[axis] += sign * velocity;
	auto window = GameContext::Get().GetMainWindow();
	float screenWidth = window->GetWidth();
	pos[axis] = std::clamp(pos[axis], 0.f, screenWidth - transformComponent.GetScale()[axis]);
	transformComponent.SetPosition(pos);

	const auto& size = transformComponent.GetScale();
	auto& colliderComponent = GameContext::Get().GetECS().GetComponentByEntityId<ColliderComponent>(m_playerEntityId);
	colliderComponent.SetPosition(pos);
}

void PlayerLogicSystem::Restart()
{
	SetInitPos();
}

void PlayerLogicSystem::SetInitPos()
{
	auto window = GameContext::Get().GetMainWindow();
	float screenWidth = window->GetWidth();
	float screenHeight = window->GetHeight();

	const std::array<float, 2>& playerSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::playerPaddleSize)];
	const std::array<float, 2> playerPos = { screenWidth * 0.5f - playerSize[0] * 0.5f,
		screenHeight - playerSize[1] };
	auto& ecs = EntityComponentSystem::Get();
	auto& transform = ecs.GetComponentByEntityId<TransformComponent>(m_playerEntityId);
	transform.SetPosition(playerPos);

	SetPosition(false, -1, 0);
}



