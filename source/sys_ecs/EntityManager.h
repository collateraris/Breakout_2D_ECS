#pragma once

#include <Component.h>

#include <unordered_map>
#include <list>
#include <cassert>

namespace breakout
{
	class EntityManager
	{
		using ComponentId = int;

		using ComponentUniqueId = int;

		using ComponentIdPair = std::pair<ComponentId, ComponentUniqueId>;

		using ComponentsIdByType = std::unordered_map<EComponentType, ComponentIdPair>;

		using EntityId = int;

		using EntityTypeId = int;

		using EntityIdList = std::list<int>;

	public:

		static EntityManager& Get();

		int Create(int entityTypeId);

		void Delete(int entityId);

		template<class componentStruct>
		void AddComponentByEntityId(int entityId, int componentId, int componentUniqueId);

		template<class componentStruct>
		int GetComponentIdByEntityId(int entityId);

		template<class componentStruct>
		bool IsContainComponentByEntityId(int entityId);

	private:

		EntityManager();
		~EntityManager();
		EntityManager(EntityManager&) = delete;
		EntityManager(EntityManager&&) = delete;
		void operator=(EntityManager&) = delete;
		void operator=(EntityManager&&) = delete;

		std::unordered_map<EntityId, ComponentsIdByType> m_entityStorage;

		std::unordered_map<EntityTypeId, EntityIdList> m_entityTypeStorage;

		int m_entityIdCounter = 0;
	};

	template<class componentStruct>
	void EntityManager::AddComponentByEntityId(int entityId, int componentId, int componentUniqueId)
	{
		EComponentType componentType = componentStruct::GetType();

		auto foundEntityIt = m_entityStorage.find(entityId);
		if (foundEntityIt == m_entityStorage.end())
		{
			ComponentsIdByType components;
			components.insert({ componentType, std::make_pair(componentId, componentUniqueId) });
			m_entityStorage[entityId] = std::move(components);
			return;
		}

		auto foundComponentIt = foundEntityIt->second.find(componentType);
		assert(foundComponentIt == foundEntityIt->second.end());

		foundEntityIt->second.insert({ componentType, std::make_pair(componentId, componentUniqueId) });
	}

	template<class componentStruct>
	int EntityManager::GetComponentIdByEntityId(int entityId)
	{
		EComponentType componentType = componentStruct::GetType();

		auto foundEntityIt = m_entityStorage.find(entityId);
		assert(foundEntityIt != m_entityStorage.end());

		auto foundComponentIt = foundEntityIt->second.find(componentType);
		assert(foundComponentIt != foundEntityIt->second.end());

		return foundComponentIt->second.first;
	}

	template<class componentStruct>
	bool EntityManager::IsContainComponentByEntityId(int entityId)
	{
		EComponentType componentType = componentStruct::GetType();

		auto foundEntityIt = m_entityStorage.find(entityId);
		assert(foundEntityIt != m_entityStorage.end());

		auto foundComponentIt = foundEntityIt->second.find(componentType);
		return foundComponentIt != foundEntityIt->second.end();
	}

}