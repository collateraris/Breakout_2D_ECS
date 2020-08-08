#include <PlayerLogicSystem.h>

#include <EntityComponentSystem.h>
#include <PlayerComponent.h>
#include <ColliderComponent.h>

#include <EventsStorage.h>

#include <gameContext.h>
#include <gameWindow.h>
#include <components/TransformComponent.h>
#include <MovementComponent.h>

#include <algorithm>

using namespace breakout;

void PlayerLogicSystem::Init()
{
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
	auto& playerComponents = EntityComponentSystem::Get().GetAllComponentsByType<PlayerComponent>();

	for (auto& player : playerComponents)
	{
		m_playerEntityId = player->GetContainer().m_entityId;
		break;
	}
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


