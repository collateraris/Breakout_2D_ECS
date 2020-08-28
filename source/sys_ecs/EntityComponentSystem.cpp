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

const EntityComponentSystem::EntityIdSet* EntityComponentSystem::GetAllEntityIdBoundWithPrefab(ComponentUniqueId uniqueId)
{
	return PrefabsManager::Get().GetAllEntityIdByComponentUniqueId(uniqueId);
}

EntityComponentSystem::ComponentId EntityComponentSystem::GetComponentId(ComponentUniqueId uniqueId)
{
	auto& foundComponentIt = m_componentUniqueIdMap.find(uniqueId);
	if (foundComponentIt == m_componentUniqueIdMap.end())
		return -1;
	return foundComponentIt->second;
}

void EntityComponentSystem::BindComponentUniqueIdWithId(ComponentUniqueId uniqueId, ComponentId id)
{
	m_componentUniqueIdMap[uniqueId] = id;
}

void EntityComponentSystem::UnbindComponentUniqueId(ComponentUniqueId uniqueId)
{
	assert(m_componentUniqueIdMap.find(uniqueId) != m_componentUniqueIdMap.end());
	m_componentUniqueIdMap.erase(uniqueId);
}

bool EntityComponentSystem::IsSameEntityType(EntityTypeId typeId, EntityId entityId)  const
{
	return EntityManager::Get().IsSameEntityType(typeId, entityId);
}
