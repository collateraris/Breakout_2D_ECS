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

void DamagableColliderLogicSystem::CollitionResolution(entityId A, entityId B)
{
	auto& ecs = EntityComponentSystem::Get();
	auto& componentA = ecs.GetComponentByEntityId<ColliderComponent>(A);
	auto& componentB = ecs.GetComponentByEntityId<ColliderComponent>(B);

	if (componentA.GetDamagableType() == EDamagableType::Destroyable)
	{
		ecs.EntityDestroy(A);
	}

	if (componentB.GetDamagableType() == EDamagableType::Destroyable)
	{
		ecs.EntityDestroy(B);
	}
}




