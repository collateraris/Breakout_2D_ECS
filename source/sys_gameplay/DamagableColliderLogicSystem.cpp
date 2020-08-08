#include <DamagableColliderLogicSystem.h>

#include <EntityComponentSystem.h>
#include <ColliderComponent.h>

#include <EventManager.h>

#include <algorithm>

using namespace breakout;

void DamagableColliderLogicSystem::Init()
{
	EventManager::Get().OnCollitionDetected().BindObject(this, &DamagableColliderLogicSystem::CollitionResolution);
}

void DamagableColliderLogicSystem::Update(float dtMilliseconds)
{

}

void DamagableColliderLogicSystem::CollitionResolution(const ColliderComponent& componentA, const ColliderComponent& componentB)
{
	auto& ecs = EntityComponentSystem::Get();

	if (componentA.GetDamagableType() == EDamagableType::Destroyable)
	{
		ecs.EntityDestroy(componentA.m_entityId);
	}

	if (componentB.GetDamagableType() == EDamagableType::Destroyable)
	{
		ecs.EntityDestroy(componentB.m_entityId);
	}
}




