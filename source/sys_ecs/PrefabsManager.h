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

	public:

		static PrefabsManager& Get();

		int GetPrefabComponentUniqueId(EntityTypeId type);

		void AddPrefabComponent(EntityTypeId type, ComponentUniqueId componentId);

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
		std::unordered_map<EntityTypeId, ComponentUniqueId> m_ComponentIdStorage;
	};
}