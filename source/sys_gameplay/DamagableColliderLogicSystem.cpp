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

	bool isExistA = ecs.IsExistEntityId(componentA.m_entityId);
	bool isExistB = ecs.IsExistEntityId(componentB.m_entityId);

	if (isExistA && componentA.GetDamagableType() == EDamagableType::Intacted
		|| isExistB && componentB.GetDamagableType() == EDamagableType::Intacted)
		return;

	if (isExistA && componentA.GetDamagableType() == EDamagableType::Destroyable)
	{
		ecs.EntityDestroy(componentA.m_entityId);
	}

	if (isExistB && componentB.GetDamagableType() == EDamagableType::Destroyable)
	{
		ecs.EntityDestroy(componentB.m_entityId);
	}
}




