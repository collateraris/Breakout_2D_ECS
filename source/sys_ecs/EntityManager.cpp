#include <EntityManager.h>

#include <ComponentManager.h>
#include <PrefabsManager.h>
#include <EntityComponentSystem.h>

#include <algorithm>

using namespace breakout;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

EntityManager& EntityManager::Get()
{
	static EntityManager entityManager;
	return entityManager;
}

int EntityManager::Create(int entityTypeId)
{
    auto foundIt = m_entityTypeStorage.find(entityTypeId);

    int id = m_entityIdCounter++;
    if (foundIt == m_entityTypeStorage.end())
    {
        m_entityTypeStorage[entityTypeId] = { id };
        return id;
    }

    foundIt->second.push_back(id);
    return id;
}

void EntityManager::Delete(int entityId)
{
    auto foundIt = m_entityStorage.find(entityId);
    if (foundIt == m_entityStorage.end())
    assert(foundIt != m_entityStorage.end());

    auto& componentManager = ComponentManager::Get();
    auto& prefabManager = PrefabsManager::Get();
    auto& ecs = EntityComponentSystem::Get();

    for (const auto& componentsIdByType : foundIt->second)
    {
        if (prefabManager.IsContains(entityId, componentsIdByType.second.second))
        {
            prefabManager.DeleteEntityId(entityId, componentsIdByType.second.second);
            continue;
        }

        componentManager.Delete(componentsIdByType.first, componentsIdByType.second.first);

        ecs.UnbindComponentUniqueId(componentsIdByType.second.second);
    }

    foundIt->second.clear();
    m_entityStorage.erase(foundIt->first);
}

bool EntityManager::IsSameEntityType(EntityTypeId typeId, EntityId entityId) const 
{
    auto& foundEntityArrIt = m_entityTypeStorage.find(typeId);
    assert(foundEntityArrIt != m_entityTypeStorage.end());
    auto& entityArr = foundEntityArrIt->second;

    return std::binary_search(entityArr.begin(), entityArr.end(), entityId);
}
