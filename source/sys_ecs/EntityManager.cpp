#include <EntityManager.h>

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
    auto foundIt = m_entityTypeCounter.find(entityTypeId);

    if (foundIt == m_entityTypeCounter.end())
    {
        m_entityTypeCounter[entityTypeId] = 0;
        return 0;
    }

    return ++foundIt->second;
}

void EntityManager::Delete(int entityId)
{
    auto foundComponentsIdIt = m_entityStorage.find(entityId);
    assert(foundComponentsIdIt != m_entityStorage.end());
    
    foundComponentsIdIt->second.clear();
    m_entityStorage.erase(entityId);
}