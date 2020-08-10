#pragma once

#include <Component.h>
#include <ComponentManager.h>
#include <EntityManager.h>
#include <FreeListPoolElement.h>

#include <unordered_map>
#include <vector>
#include <array>

namespace breakout
{
	class EntityComponentSystem
	{
		using ComponentIdCounter = unsigned int;

	public:

		static EntityComponentSystem& Get();

		template<class componentStruct>
		const std::unordered_set<FreeListPoolElement<componentStruct>*>& GetAllComponentsByType();

		template<class componentStruct>
		componentStruct& AddComponentByEntityId(int entityId);

		template<class componentStruct>
		componentStruct& GetComponentByEntityId(int entityId);

		template<class componentStruct>
		bool IsContainComponentByEntityId(int entityId);

		void EntityDestroy(int entityId);

		int CreateEntityByEntityTypeId(int entityTypeId);

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