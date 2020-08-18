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

int PrefabsManager::GetPrefabComponentId(EntityTypeId type)
{
	auto foundComponentIt = m_ComponentIdStorage.find(type);
	if (foundComponentIt == m_ComponentIdStorage.end())
		return static_cast<int>(EPrefabsIndexState::INDEX_NONE);
	return foundComponentIt->second;
}

void PrefabsManager::AddPrefabComponent(EntityTypeId type, ComponentId componentId)
{
	m_ComponentIdStorage[type] = componentId;
}

void PrefabsManager::BindEntityIdWithComponentId(EntityTypeId type, EntityId id)
{
	auto foundComponentIt = m_ComponentIdStorage.find(type);
	assert(foundComponentIt != m_ComponentIdStorage.end());

	ComponentId componentId = foundComponentIt->second;
	auto foundEntityIt = m_EntityIdStorage.find(componentId);
	if (foundEntityIt == m_EntityIdStorage.end())
	{
		m_EntityIdStorage[componentId] = { id };
	}
	else
	{
		m_EntityIdStorage[componentId].insert(id);
	}
}

void PrefabsManager::DeleteEntityId(EntityId id, ComponentId componentId)
{
	assert(m_EntityIdStorage.find(componentId) != m_EntityIdStorage.end());
	m_EntityIdStorage[componentId].erase(id);

	if (m_EntityIdStorage.find(componentId)->second.empty())
	{
		m_EntityIdStorage.erase(componentId);
	}
}

bool PrefabsManager::IsContains(EntityId id, ComponentId componentId)
{
	auto& foundEntitySetIt = m_EntityIdStorage.find(componentId);
	if (foundEntitySetIt == m_EntityIdStorage.end())
		return false;
	return foundEntitySetIt->second.find(id) != foundEntitySetIt->second.end();
}

const PrefabsManager::EntityIdSet* PrefabsManager::GetAllEntityIdByComponentId(ComponentId componentId)
{
	auto& foundEntitySetIt = m_EntityIdStorage.find(componentId);
	if (foundEntitySetIt == m_EntityIdStorage.end())
		return nullptr;
	return &foundEntitySetIt->second;
}