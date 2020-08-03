#include <EntityManager.h>

#include <ComponentManager.h>

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
    assert(foundIt != m_entityStorage.end());

    auto& componentManager = ComponentManager::Get();

    for (auto& componentsIdByType : foundIt->second)
    {
        componentManager.Delete(componentsIdByType.first, componentsIdByType.second);
    }

    foundIt->second.clear();
    m_entityStorage.erase(foundIt->first);
}
