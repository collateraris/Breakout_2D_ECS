#include <EntityComponentSystem.h>

#include <SpriteComponent.h>
#include <components/TransformComponent.h>


using namespace breakout;

EntityComponentSystem::EntityComponentSystem()
{

}

EntityComponentSystem::~EntityComponentSystem()
{

}

EntityComponentSystem& EntityComponentSystem::Get()
{
	static EntityComponentSystem ecs;
	return ecs;
}

int EntityComponentSystem::CreateEntityByEntityTypeId(int entityTypeId)
{
	return EntityManager::Get().Create(entityTypeId);
}

void EntityComponentSystem::EntityDestroy(int entityId)
{
	EntityManager::Get().Delete(entityId);
}

const EntityComponentSystem::EntityIdSet* EntityComponentSystem::GetAllEntityIdBoundWithPrefab(ComponentId componentId)
{
	return PrefabsManager::Get().GetAllEntityIdByComponentId(componentId);
}
