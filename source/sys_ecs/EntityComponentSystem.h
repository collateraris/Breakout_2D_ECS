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

		const EntityIdSet* GetAllEntityIdBoundWithPrefab(ComponentId componentId);

	private:

		EntityComponentSystem();
		~EntityComponentSystem();
		EntityComponentSystem(EntityComponentSystem&) = delete;
		EntityComponentSystem(EntityComponentSystem&&) = delete;
		void operator=(EntityComponentSystem&) = delete;
		void operator=(EntityComponentSystem&&) = delete;

		std::array<ComponentIdCounter, static_cast<size_t>(EComponentType::MAX)> m_usedComponentsCounter = {0};
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

		EntityManager::Get().AddComponentByEntityId<componentStruct>(component.m_entityId, component.m_componentId);

		return component;
	}

	template<class componentStruct>
	componentStruct* EntityComponentSystem::AddPrefabComponentByEntityId(EntityTypeId typeId, EntityId entityId)
	{
		PrefabsManager& prefabsManager = PrefabsManager::Get();
		ComponentId componentId = prefabsManager.GetPrefabComponentId(typeId);
		if (componentId == static_cast<int>(EPrefabsIndexState::INDEX_NONE))
		{
			EComponentType type = componentStruct::GetType();
			auto& component = ComponentManager::Get().NextComponentActivate<componentStruct>();
			if (component.m_componentId == -1)
			{
				unsigned int componentId = m_usedComponentsCounter[static_cast<size_t>(type)]++;
				component.m_componentId = static_cast<int>(componentId);
			}
			component.m_entityId = static_cast<int>(EEntityIdStatus::PREFABS_CONTAINER);
			prefabsManager.AddPrefabComponent(typeId, component.m_componentId);
			prefabsManager.BindEntityIdWithComponentId(typeId, entityId);
			EntityManager::Get().AddComponentByEntityId<componentStruct>(entityId, component.m_componentId);
			return &component;
		}

		prefabsManager.BindEntityIdWithComponentId(typeId, entityId);
		EntityManager::Get().AddComponentByEntityId<componentStruct>(entityId, componentId);
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