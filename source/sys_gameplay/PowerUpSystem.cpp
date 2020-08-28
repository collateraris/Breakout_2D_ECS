#include <PowerUpSystem.h>

#include <components/TransformComponent.h>
#include <ColliderComponent.h>
#include <CollisionSystem.h>
#include <PowerUpComponent.h>
#include <FreeListPoolElement.h>
#include <EventManager.h>

#include <ECSBreakout.h>
#include <EntityComponentSystem.h>

#include <ctime>
#include <cassert>

using namespace breakout;

void PowerUpLogicSystem::Init()
{
	EventManager::Get().OnCollitionDetected().BindObject(this, &PowerUpLogicSystem::CollitionResolution);
}

void PowerUpLogicSystem::Update(float dtMilliseconds)
{
    auto& ecs = EntityComponentSystem::Get();
    const auto& allPowerUpComponents = ecs.GetAllComponentsByType<PowerUpComponent>();

    for (auto& component: allPowerUpComponents)
    {
        auto& powerUpComponent = static_cast<FreeListPoolElement<PowerUpComponent>*>(component)->GetContainer();
        assert(powerUpComponent.m_entityId == static_cast<int>(EEntityIdStatus::PREFABS_CONTAINER));

        auto entityIdSet = ecs.GetAllEntityIdBoundWithPrefab(powerUpComponent.m_componentUniqueId);
        if (!entityIdSet)
            continue;

        for (auto& powerUpId : *entityIdSet)
        {
            MoveLogic(powerUpId, dtMilliseconds);
        }
    }
}

void PowerUpLogicSystem::MoveLogic(PowerUpEntityId entityId, float dtMilliseconds)
{

}

void PowerUpLogicSystem::CollitionResolution(const ColliderComponent&, const ColliderComponent&)
{

}

bool PowerUpLogicSystem::ShouldSpawn(unsigned int chance)
{
	std::srand(std::time(nullptr));
	unsigned int random = rand() % chance;
	return random == 0;
}

void PowerUpLogicSystem::SpawnPowerUps(TransformComponent& initPosition)
{
    if (ShouldSpawn(75)) // 1 in 75 chance
    {
        int speedPowerUpId = ECSBreakout::CreateComponent(EEntityType::SpeedPowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(speedPowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(75))
    {
        int stickyPowerUpId = ECSBreakout::CreateComponent(EEntityType::StickyPowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(stickyPowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(75))
    {
        int passThroughPowerUpId = ECSBreakout::CreateComponent(EEntityType::PassThroughPowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(passThroughPowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(75))
    {
        int padSizeIncreasePowerUpId = ECSBreakout::CreateComponent(EEntityType::PadSizeIncreasePowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(padSizeIncreasePowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(15)) // negative powerups should spawn more often
    {
        int confusePowerUpId = ECSBreakout::CreateComponent(EEntityType::ConfusePowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(confusePowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(15))
    {
        int chaosPowerUpId = ECSBreakout::CreateComponent(EEntityType::ChaosPowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(chaosPowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        return;
    }
}