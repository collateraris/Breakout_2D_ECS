#include <PowerUpSystem.h>

#include <components/TransformComponent.h>
#include <ColliderComponent.h>
#include <TimerComponent.h>
#include <CollisionSystem.h>
#include <PowerUpComponent.h>
#include <FreeListPoolElement.h>
#include <EventManager.h>
#include <PostEffectsStateManager.h>
#include <APostEffectState.h>

#include <ECSBreakout.h>
#include <EntityComponentSystem.h>
#include <gameContext.h>

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
            TimerLogic(powerUpId, dtMilliseconds);
            PowerUpOutsideLogic(powerUpId);
        }
    }

    DeleteEntityFromDieList();
}

void PowerUpLogicSystem::MoveLogic(PowerUpEntityId entityId, float dtMilliseconds)
{
    auto& ecs = EntityComponentSystem::Get();
    auto& powerUpTransform = ecs.GetComponentByEntityId<TransformComponent>(entityId);
    auto& powerUpCollider = ecs.GetComponentByEntityId<ColliderComponent>(entityId);

    Vector2<float> pos = powerUpTransform.GetPosition();
    Vector2<float> powerUpVelocity = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::powerUpVelocity)];
    pos += powerUpVelocity * dtMilliseconds;
    powerUpTransform.SetPosition(pos.data());
    powerUpCollider.SetPosition(pos.data());
}

void PowerUpLogicSystem::TimerLogic(PowerUpEntityId entityId, float dtMilliseconds)
{
    auto& ecs = EntityComponentSystem::Get();
    auto& timer = ecs.GetComponentByEntityId<TimerComponent>(entityId);
    
    if (!timer.bActivated)
        return;
    timer.m_Duration -= timer.m_DecaySpeed * dtMilliseconds;

    if (timer.m_Duration <= 0)
    {
        timer.bActivated = false;
        DeactivatePowerUp(entityId);
        AddCandidateToDieList(entityId);
    }
}

void PowerUpLogicSystem::PowerUpOutsideLogic(PowerUpEntityId entityId)
{
    auto& ecs = EntityComponentSystem::Get();
    auto& timer = ecs.GetComponentByEntityId<TimerComponent>(entityId);

    if (timer.bActivated)
        return;

    int w, h;
    GameContext::Get().GetMainWindowSize(w, h);
    float screenHeight = static_cast<float>(h);

    auto& transform = ecs.GetComponentByEntityId<TransformComponent>(entityId);
    auto& pos = transform.GetPosition();
    auto& size = transform.GetScale();

    if (pos[1] + size[1] >= screenHeight)
    {
        AddCandidateToDieList(entityId);
    }
}

void PowerUpLogicSystem::CollitionResolution(const ColliderComponent& componentA, const ColliderComponent& componentB)
{
    auto& ecs = EntityComponentSystem::Get();
    if (!(ecs.IsExistEntityId(componentA.m_entityId) && ecs.IsExistEntityId(componentB.m_entityId)))
        return;

    if (ecs.IsSameEntityType(static_cast<int>(EEntityType::PlayerBall), componentA.m_entityId)
       && ecs.IsSameEntityType(static_cast<int>(EEntityType::Block), componentB.m_entityId))
    {
        auto& blockTransform = ecs.GetComponentByEntityId<TransformComponent>(componentB.m_entityId);
        SpawnPowerUps(blockTransform);
    }
    else if (ecs.IsSameEntityType(static_cast<int>(EEntityType::PlayerBall), componentB.m_entityId)
        && ecs.IsSameEntityType(static_cast<int>(EEntityType::Block), componentA.m_entityId))
    {
        auto& blockTransform = ecs.GetComponentByEntityId<TransformComponent>(componentA.m_entityId);
        SpawnPowerUps(blockTransform);
    }
    else if (ecs.IsContainComponentByEntityId<PowerUpComponent>(componentA.m_entityId)
        && ecs.IsSameEntityType(static_cast<int>(EEntityType::PlayerPaddle), componentB.m_entityId))
    {
        ActivatePowerUp(componentA.m_entityId);
    }
    else if (ecs.IsContainComponentByEntityId<PowerUpComponent>(componentB.m_entityId)
        && ecs.IsSameEntityType(static_cast<int>(EEntityType::PlayerPaddle), componentA.m_entityId))
    {
        ActivatePowerUp(componentB.m_entityId);
    }
}

bool PowerUpLogicSystem::ShouldSpawn(unsigned int chance)
{
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
        auto& collider = EntityComponentSystem::Get()
            .GetComponentByEntityId<ColliderComponent>(speedPowerUpId);
        collider.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(75))
    {
        int stickyPowerUpId = ECSBreakout::CreateComponent(EEntityType::StickyPowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(stickyPowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        auto& collider = EntityComponentSystem::Get()
            .GetComponentByEntityId<ColliderComponent>(stickyPowerUpId);
        collider.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(75))
    {
        int passThroughPowerUpId = ECSBreakout::CreateComponent(EEntityType::PassThroughPowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(passThroughPowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        auto& collider = EntityComponentSystem::Get()
            .GetComponentByEntityId<ColliderComponent>(passThroughPowerUpId);
        collider.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(75))
    {
        int padSizeIncreasePowerUpId = ECSBreakout::CreateComponent(EEntityType::PadSizeIncreasePowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(padSizeIncreasePowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        auto& collider = EntityComponentSystem::Get()
            .GetComponentByEntityId<ColliderComponent>(padSizeIncreasePowerUpId);
        collider.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(15) || true) // negative powerups should spawn more often
    {
        int confusePowerUpId = ECSBreakout::CreateComponent(EEntityType::ConfusePowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(confusePowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        auto& collider = EntityComponentSystem::Get()
            .GetComponentByEntityId<ColliderComponent>(confusePowerUpId);
        collider.SetPosition(initPosition.GetPosition());
        return;
    }

    if (ShouldSpawn(15) || true)
    {
        int chaosPowerUpId = ECSBreakout::CreateComponent(EEntityType::ChaosPowerUp);
        auto& transform = EntityComponentSystem::Get()
            .GetComponentByEntityId<TransformComponent>(chaosPowerUpId);
        transform.SetPosition(initPosition.GetPosition());
        auto& collider = EntityComponentSystem::Get()
            .GetComponentByEntityId<ColliderComponent>(chaosPowerUpId);
        collider.SetPosition(initPosition.GetPosition());
        return;
    }
}

void PowerUpLogicSystem::ActivatePowerUp(PowerUpEntityId id)
{
    auto& ecs = EntityComponentSystem::Get();
    auto& powerUpComponent = ecs.GetComponentByEntityId<PowerUpComponent>(id);

    EPowerUpType type = powerUpComponent.powerUpType;
    switch (type)
    {
    case breakout::EPowerUpType::None:
        break;
    case breakout::EPowerUpType::Speed:
        break;
    case breakout::EPowerUpType::Sticky:
        break;
    case breakout::EPowerUpType::PassThrough:
        break;
    case breakout::EPowerUpType::PadSizeIncrease:
        break;
    case breakout::EPowerUpType::Confuse:
        ActivateTimer(id, 15.f, 2.f);
        SwitchPostEffect(id, static_cast<int>(EPostEffectStates::Confuse));
        break;
    case breakout::EPowerUpType::Chaos:
        ActivateTimer(id, 15.f, 2.f);
        SwitchPostEffect(id, static_cast<int>(EPostEffectStates::Chaos));
        break;
    default:
        break;
    }
}

void PowerUpLogicSystem::SwitchPostEffect(PowerUpEntityId id, int new_effect)
{
    m_currPostEffectEntityId = id;
    PostEffectsStateManager::Get().SwitchState(new_effect);
}

void PowerUpLogicSystem::DeactivatePowerUp(PowerUpEntityId id)
{
    auto& ecs = EntityComponentSystem::Get();
    auto& powerUpComponent = ecs.GetComponentByEntityId<PowerUpComponent>(id);

    EPowerUpType type = powerUpComponent.powerUpType;
    switch (type)
    {
    case breakout::EPowerUpType::None:
        break;
    case breakout::EPowerUpType::Speed:
        break;
    case breakout::EPowerUpType::Sticky:
        break;
    case breakout::EPowerUpType::PassThrough:
        break;
    case breakout::EPowerUpType::PadSizeIncrease:
        break;
    case breakout::EPowerUpType::Confuse:
        TrySetIdlePostEffect(id);
        break;
    case breakout::EPowerUpType::Chaos:
        TrySetIdlePostEffect(id);
        break;
    default:
        break;
    }
}

void PowerUpLogicSystem::TrySetIdlePostEffect(PowerUpEntityId id)
{
    if (m_currPostEffectEntityId != id)
        return;
    PostEffectsStateManager::Get().SwitchState(static_cast<int>(EPostEffectStates::Idle));
}

void PowerUpLogicSystem::AddCandidateToDieList(PowerUpEntityId entityId)
{
    if (m_currentDieListPos < m_dieListCandidate.size())
    {
        m_dieListCandidate[m_currentDieListPos++] = entityId;
    }
    else
    {
        m_dieListCandidate.push_back(entityId);
        m_currentDieListPos++;
    }
}

void PowerUpLogicSystem::DeleteEntityFromDieList()
{
    auto& ecs = EntityComponentSystem::Get();

    for (auto& id : m_dieListCandidate)
    {
        if (ecs.IsExistEntityId(id))
            ecs.EntityDestroy(id);
    }

    m_currentDieListPos = 0;
}

void PowerUpLogicSystem::ActivateTimer(PowerUpEntityId id, float duration, float decaySpeed)
{
    auto& ecs = EntityComponentSystem::Get();
    auto& timer = ecs.GetComponentByEntityId<TimerComponent>(id);

    timer.m_Duration = duration;
    timer.m_DecaySpeed = decaySpeed;
    timer.bActivated = true;
}