#include <PrefabsManager.h>

using namespace breakout;

PrefabsManager::PrefabsManager()
{

}

PrefabsManager::~PrefabsManager()
{

}

PrefabsManager& PrefabsManager::Get()
{
	static PrefabsManager prefabsManager;
	return prefabsManager;
}

void PrefabsManager::DeleteEntityId(EntityId id, ComponentUniqueId componentId)
{
	assert(m_EntityIdStorage.find(componentId) != m_EntityIdStorage.end());
	m_EntityIdStorage[componentId].erase(id);

	if (m_EntityIdStorage.find(componentId)->second.empty())
	{
		m_EntityIdStorage.erase(componentId);
	}
}

bool PrefabsManager::IsContains(EntityId id, ComponentUniqueId componentId)
{
	auto& foundEntitySetIt = m_EntityIdStorage.find(componentId);
	if (foundEntitySetIt == m_EntityIdStorage.end())
		return false;
	return foundEntitySetIt->second.find(id) != foundEntitySetIt->second.end();
}

const PrefabsManager::EntityIdSet* PrefabsManager::GetAllEntityIdByComponentUniqueId(ComponentUniqueId componentId)
{
	auto& foundEntitySetIt = m_EntityIdStorage.find(componentId);
	if (foundEntitySetIt == m_EntityIdStorage.end())
		return nullptr;
	return &foundEntitySetIt->second;
}