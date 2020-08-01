#pragma once

#include <Component.h>

#include <unordered_map>
#include <cassert>

namespace breakout
{
	class EntityManager
	{
		using ComponentId = int;

		using ComponentsIdByType = std::unordered_map<EComponentType, ComponentId>;

		using EntityId = int;

	public:

		static EntityManager& Get();

		template<class componentStruct>
		void AddComponentByEntityId(int entityId, int componentId);

	private:

		EntityManager();
		~EntityManager();
		EntityManager(EntityManager&) = delete;
		EntityManager(EntityManager&&) = delete;
		void operator=(EntityManager&) = delete;
		void operator=(EntityManager&&) = delete;

		std::unordered_map<EntityId, ComponentsIdByType> m_entityStorage;
	};

	template<class componentStruct>
	void EntityManager::AddComponentByEntityId(int entityId, int componentId)
	{
		EComponentType componentType = componentStruct::GetType();

		auto foundEntityIt = m_entityStorage.find(entityId);
		if (foundEntityIt == m_entityStorage.end())
		{
			ComponentsIdByType components;
			components[componentType] = componentId;
			m_entityStorage[entityId] = std::move(components);
			return;
		}

		auto foundComponentIt = foundEntityIt->second.find(componentType);
		assert(foundComponentIt == foundEntityIt->second.end());

		foundEntityIt->second[componentType] = componentId;
	}
}