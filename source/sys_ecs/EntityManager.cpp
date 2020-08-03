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
