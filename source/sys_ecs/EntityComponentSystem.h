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
	public:

		static EntityComponentSystem& Get();

		template<class componentStruct>
		const std::vector<FreeListPoolElement<componentStruct>>& GetAllComponentsByType();

		template<typename componentStruct>
		componentStruct& AddComponentByEntityId(int entityId);

	private:

		EntityComponentSystem();
		~EntityComponentSystem();
		EntityComponentSystem(EntityComponentSystem&) = delete;
		EntityComponentSystem(EntityComponentSystem&&) = delete;
		void operator=(EntityComponentSystem&) = delete;
		void operator=(EntityComponentSystem&&) = delete;

		std::array<unsigned int, static_cast<size_t>(EComponentType::MAX)> m_usedComponentsCounter = {0};
	};

	template<class componentStruct>
	const std::vector<FreeListPoolElement<componentStruct>>& EntityComponentSystem::GetAllComponentsByType()
	{
		return ComponentManager::Get().GetComponents<componentStruct>();
	}

	template<typename componentStruct>
	componentStruct& EntityComponentSystem::AddComponentByEntityId(int entityId)
	{
		EComponentType type = componentStruct::GetType();
		unsigned int componentId = m_usedComponentsCounter[static_cast<size_t>(type)]++;

		auto& component = ComponentManager::Get().NextComponentActivate<componentStruct>();
		component.m_componentId = static_cast<int>(componentId);
		component.m_entityId = entityId;

		EntityManager::Get().AddComponentByEntityId<componentStruct>(component.m_entityId, component.m_componentId);

		return component;
	}
}