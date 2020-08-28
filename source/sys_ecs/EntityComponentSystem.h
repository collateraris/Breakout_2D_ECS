#pragma once

#include <Component.h>
#include <ComponentManager.h>
#include <EntityManager.h>
#include <PrefabsManager.h>
#include <FreeListPoolElement.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>

namespace breakout
{
	enum class EEntityIdStatus: int
	{
		INDEX_NONE = -1,
		PREFABS_CONTAINER = -5,
	};

	class EntityComponentSystem
	{
		using ComponentId = int;
		using ComponentUniqueId = int;

		using ComponentIdCounter = unsigned int;

		using EntityId = int;

		using EntityTypeId = int;

		using EntityIdSet = std::unordered_set<EntityId>;

	public:

		static EntityComponentSystem& Get();

		template<class componentStruct>
		const std::unordered_set<FreeListPoolElement<componentStruct>*>& GetAllComponentsByType();

		template<class componentStruct>
		componentStruct& AddComponentByEntityId(int entityId);

		template<class componentStruct>
		componentStruct* AddPrefabComponentByEntityId(EntityTypeId typeId, EntityId entityId);

		template<class componentStruct>
		componentStruct& GetComponentByEntityId(int entityId);

		template<class componentStruct>
		bool IsContainComponentByEntityId(int entityId);

		void EntityDestroy(int entityId);

		int CreateEntityByEntityTypeId(int entityTypeId);

		const EntityIdSet* GetAllEntityIdBoundWithPrefab(ComponentUniqueId componentId);

		ComponentId GetComponentId(ComponentUniqueId uniqueId);
		void UnbindComponentUniqueId(ComponentUniqueId);

		bool IsSameEntityType(EntityTypeId, EntityId) const;

		bool IsExistEntityId(EntityId) const;

	private:

		EntityComponentSystem();
		~EntityComponentSystem();
		EntityComponentSystem(EntityComponentSystem&) = delete;
		EntityComponentSystem(EntityComponentSystem&&) = delete;
		void operator=(EntityComponentSystem&) = delete;
		void operator=(EntityComponentSystem&&) = delete;

		void BindComponentUniqueIdWithId(ComponentUniqueId, ComponentId);

		std::array<ComponentIdCounter, static_cast<size_t>(EComponentType::MAX)> m_usedComponentsCounter = {0};

		std::unordered_map<ComponentUniqueId, ComponentId> m_componentUniqueIdMap;

		unsigned int m_usedComponentUniqueId = 0;
	};

	template<class componentStruct>
	const std::unordered_set<FreeListPoolElement<componentStruct>*>& EntityComponentSystem::GetAllComponentsByType()
	{
		return ComponentManager::Get().GetComponents<componentStruct>();
	}

	template<class componentStruct>
	componentStruct& EntityComponentSystem::AddComponentByEntityId(int entityId)
	{
		EComponentType type = componentStruct::GetType();

		auto& component = ComponentManager::Get().NextComponentActivate<componentStruct>();
		if (component.m_componentId == -1)
		{
			unsigned int componentId = m_usedComponentsCounter[static_cast<size_t>(type)]++;
			component.m_componentId = static_cast<int>(componentId);
		}
		component.m_entityId = entityId;
		component.m_componentUniqueId = m_usedComponentUniqueId++;
		BindComponentUniqueIdWithId(component.m_componentUniqueId, component.m_componentId);

		EntityManager::Get().AddComponentByEntityId<componentStruct>(component.m_entityId, component.m_componentId, component.m_componentUniqueId);

		return component;
	}

	template<class componentStruct>
	componentStruct* EntityComponentSystem::AddPrefabComponentByEntityId(EntityTypeId typeId, EntityId entityId)
	{
		PrefabsManager& prefabsManager = PrefabsManager::Get();
		ComponentUniqueId componentUniqueId = prefabsManager.GetPrefabComponentUniqueId<componentStruct>(typeId);
		if (componentUniqueId == static_cast<int>(EPrefabsIndexState::INDEX_NONE))
		{
			EComponentType type = componentStruct::GetType();
			auto& component = ComponentManager::Get().NextComponentActivate<componentStruct>();
			if (component.m_componentId == -1)
			{
				unsigned int componentId = m_usedComponentsCounter[static_cast<size_t>(type)]++;
				component.m_componentId = static_cast<int>(componentId);
			}
			component.m_entityId = static_cast<int>(EEntityIdStatus::PREFABS_CONTAINER);
			component.m_componentUniqueId = m_usedComponentUniqueId++;
			BindComponentUniqueIdWithId(component.m_componentUniqueId, component.m_componentId);

			prefabsManager.AddPrefabComponent<componentStruct>(typeId, component.m_componentUniqueId);
			prefabsManager.BindEntityIdWithComponentUniqueId<componentStruct>(typeId, entityId);
			EntityManager::Get().AddComponentByEntityId<componentStruct>(entityId, component.m_componentId, component.m_componentUniqueId);
			return &component;
		}

		prefabsManager.BindEntityIdWithComponentUniqueId<componentStruct>(typeId, entityId);
		EntityManager::Get().AddComponentByEntityId<componentStruct>(entityId, GetComponentId(componentUniqueId), componentUniqueId);
		return nullptr;

	}

	template<class componentStruct>
	componentStruct& EntityComponentSystem::GetComponentByEntityId(int entityId)
	{
		int componentId = EntityManager::Get().GetComponentIdByEntityId<componentStruct>(entityId);
		auto& component = ComponentManager::Get().GetComponent<componentStruct>(componentId);
		return component;
	}

	template<class componentStruct>
	bool EntityComponentSystem::IsContainComponentByEntityId(int entityId)
	{
		return EntityManager::Get().IsContainComponentByEntityId<componentStruct>(entityId);
	}
}