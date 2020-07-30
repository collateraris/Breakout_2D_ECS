#pragma once

#include <Component.h>

#include <FreeListObjectPool.h>
#include <FreeListPoolElement.h>

#include <unordered_map>
#include <functional>
#include <any>

namespace breakout
{
	class ComponentManager
	{
	public:

		static ComponentManager& Get();

		template<class componentStruct>
		void CreateComponentPool(unsigned int poolSize);

		template<class componentStruct>
		void Delete(int componentId);

		template<class componentStruct>
		componentStruct& GetComponent(int componentId);

		template<class componentStruct>
		unsigned int GetPoolSize();

		template<class componentStruct>
		void DeleteAll();

		template<class componentStruct>
		bool IsContainAvailablePlace() const;

	private:

		ComponentManager();
		~ComponentManager();
		ComponentManager(ComponentManager&) = delete;
		ComponentManager(ComponentManager&&) = delete;
		void operator=(ComponentManager&) = delete;
		void operator=(ComponentManager&&) = delete;

		using ObjPool = std::any;

		template<class componentStruct>
		using ComponentPool = FreeListObjectPool<FreeListPoolElement<componentStruct>>;

		std::unordered_map<EComponentType, ObjPool> m_componentsPools;
	};

	template<class componentStruct>
	void ComponentManager::CreateComponentPool(unsigned int poolSize)
	{
		EComponentType type = componentStruct::GetType();

		m_componentsPools[type] = std::move(FreeListObjectPool<FreeListPoolElement<componentStruct>>(poolSize));
	}

	template<class componentStruct>
	void ComponentManager::Delete(int componentId)
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());

		std::any_cast<ComponentPool<componentStruct>>(foundIt->second).Deactivate(componentId);
	}

	template<class componentStruct>
	componentStruct& ComponentManager::GetComponent(int componentId)
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());

		return std::any_cast<ComponentPool<componentStruct>>(foundIt->second).GetPoolElement(componentId).GetLive();
	}

	template<class componentStruct>
	unsigned int ComponentManager::GetPoolSize()
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());

		return std::any_cast<ComponentPool<componentStruct>>(foundIt->second).GetPoolSize();
	}

	template<class componentStruct>
	void ComponentManager::DeleteAll()
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());

		std::any_cast<ComponentPool<componentStruct>>(foundIt->second).DeactivateAll();
	}

	template<class componentStruct>
	bool ComponentManager::IsContainAvailablePlace() const
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());

		return std::any_cast<ComponentPool<componentStruct>>(foundIt->second).IsContainAvailablePlace();
	}
}