#pragma once

#include <unordered_map>
#include <unordered_set>
#include <cassert>

namespace breakout
{
	enum class EPrefabsIndexState
	{
		INDEX_NONE,
	};

	class PrefabsManager
	{
		using ComponentUniqueId = int;
		using EntityId = int;
		using EntityIdSet = std::unordered_set<EntityId>;
		using EntityTypeId = int;
		using ComponentTypeId = int;

	public:

		static PrefabsManager& Get();

		template<class componentStruct>
		int GetPrefabComponentUniqueId(EntityTypeId type);

		template<class componentStruct>
		void AddPrefabComponent(EntityTypeId type, ComponentUniqueId componentId);

		template<class componentStruct>
		void BindEntityIdWithComponentUniqueId(EntityTypeId type, EntityId id);

		void DeleteEntityId(EntityId id, ComponentUniqueId componentId);

		bool IsContains(EntityId id, ComponentUniqueId componentId);

		const EntityIdSet* GetAllEntityIdByComponentUniqueId(ComponentUniqueId componentId);

	private:

		PrefabsManager();
		~PrefabsManager();
		PrefabsManager(PrefabsManager&) = delete;
		PrefabsManager(PrefabsManager&&) = delete;
		void operator=(PrefabsManager&) = delete;
		void operator=(PrefabsManager&&) = delete;

		std::unordered_map<ComponentUniqueId, EntityIdSet> m_EntityIdStorage;
		std::unordered_map<EntityTypeId, std::unordered_map<ComponentTypeId, ComponentUniqueId>> m_ComponentIdStorage;
	};

	template<class componentStruct>
	int PrefabsManager::GetPrefabComponentUniqueId(EntityTypeId type)
	{
		auto& foundComponentIt = m_ComponentIdStorage.find(type);
		if (foundComponentIt == m_ComponentIdStorage.end())
			return static_cast<int>(EPrefabsIndexState::INDEX_NONE);
		ComponentTypeId typeId = static_cast<int>(componentStruct::GetType());
		auto& componentMap = foundComponentIt->second;
		auto& foundUniqueId = componentMap.find(typeId);
		if (foundUniqueId == componentMap.end())
			return static_cast<int>(EPrefabsIndexState::INDEX_NONE);
		ComponentUniqueId uniqueId = foundUniqueId->second;
		return uniqueId;
	}

	template<class componentStruct>
	void PrefabsManager::AddPrefabComponent(EntityTypeId type, ComponentUniqueId uniqueId)
	{
		ComponentTypeId typeId = static_cast<int>(componentStruct::GetType());
		m_ComponentIdStorage[type][typeId] = uniqueId;
	}

	template<class componentStruct>
	void PrefabsManager::BindEntityIdWithComponentUniqueId(EntityTypeId type, EntityId id)
	{
		auto foundComponentIt = m_ComponentIdStorage.find(type);
		assert(foundComponentIt != m_ComponentIdStorage.end());

		ComponentTypeId typeId = static_cast<int>(componentStruct::GetType());
		auto& componentMap = foundComponentIt->second;
		auto& foundUniqueId = componentMap.find(typeId);
		assert(foundUniqueId != componentMap.end());

		ComponentUniqueId uniqueId = foundUniqueId->second;
		auto foundEntityIt = m_EntityIdStorage.find(uniqueId);
		if (foundEntityIt == m_EntityIdStorage.end())
		{
			m_EntityIdStorage[uniqueId] = { id };
		}
		else
		{
			m_EntityIdStorage[uniqueId].insert(id);
		}
	}
}