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
		using ComponentId = int;
		using EntityId = int;
		using EntityIdSet = std::unordered_set<EntityId>;
		using EntityTypeId = int;

	public:

		static PrefabsManager& Get();

		int GetPrefabComponentId(EntityTypeId type);

		void AddPrefabComponent(EntityTypeId type, ComponentId componentId);

		void BindEntityIdWithComponentId(EntityTypeId type, EntityId id);

		void DeleteEntityId(EntityId id, ComponentId componentId);

		bool IsContains(EntityId id, ComponentId componentId);

		const EntityIdSet* GetAllEntityIdByComponentId(ComponentId componentId);

	private:

		PrefabsManager();
		~PrefabsManager();
		PrefabsManager(PrefabsManager&) = delete;
		PrefabsManager(PrefabsManager&&) = delete;
		void operator=(PrefabsManager&) = delete;
		void operator=(PrefabsManager&&) = delete;

		std::unordered_map<ComponentId, EntityIdSet> m_EntityIdStorage;
		std::unordered_map<EntityTypeId, ComponentId> m_ComponentIdStorage;
	};
}