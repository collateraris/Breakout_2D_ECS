#pragma once

#include <Component.h>

#include <FreeListObjectPool.h>
#include <FreeListPoolElement.h>

#include <unordered_map>
#include <functional>
#include <any>
#include <vector>

#include <iostream>

namespace breakout
{
	class ComponentManager
	{
		using ObjPool = std::any;

		template<class componentStruct>
		using ComponentPool = FreeListObjectPool<FreeListPoolElement<componentStruct>>;

	public:

		static ComponentManager& Get();

		template<class componentStruct>
		void CreateComponentPool(unsigned int poolSize);

		template<class componentStruct>
		componentStruct& NextComponentActivate();

		template<class componentStruct>
		componentStruct& GetComponent(int componentId);

		template<class componentStruct>
		unsigned int GetPoolSize();

		template<class componentStruct>
		void DeleteAll();

		template<class componentStruct>
		void Delete(int componentId);

		void Delete(EComponentType type, int componentId);

		template<class componentStruct>
		const std::unordered_set<FreeListPoolElement<componentStruct>*>& GetComponents();

		template<class componentStruct>
		bool IsContainAvailablePlace() const;

	private:

		ComponentManager();
		~ComponentManager();
		ComponentManager(ComponentManager&) = delete;
		ComponentManager(ComponentManager&&) = delete;
		void operator=(ComponentManager&) = delete;
		void operator=(ComponentManager&&) = delete;

		std::unordered_map<EComponentType, ObjPool> m_componentsPools;
	};

	template<class componentStruct>
	void ComponentManager::CreateComponentPool(unsigned int poolSize)
	{
		EComponentType type = componentStruct::GetType();

		m_componentsPools[type] = std::make_any<FreeListObjectPool<FreeListPoolElement<componentStruct>>>(poolSize);
	}

	template<class componentStruct>
	componentStruct& ComponentManager::NextComponentActivate()
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());
		assert(foundIt->second.has_value());

		componentStruct& component = std::any_cast<ComponentPool<componentStruct>>(&foundIt->second)
			->Activate().GetContainer();

		return component;
	}

	template<class componentStruct>
	componentStruct& ComponentManager::GetComponent(int componentId)
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());
		assert(foundIt->second.has_value());

		componentStruct& component = std::any_cast<ComponentPool<componentStruct>>(&foundIt->second)
			->GetPoolElement(componentId).GetContainer();

		return component;
	}

	template<class componentStruct>
	unsigned int ComponentManager::GetPoolSize()
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());
		assert(foundIt->second.has_value());

		return std::any_cast<ComponentPool<componentStruct>>(&foundIt->second)->GetPoolSize();
	}

	template<class componentStruct>
	void ComponentManager::DeleteAll()
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());
		assert(foundIt->second.has_value());

		std::any_cast<ComponentPool<componentStruct>>(&foundIt->second)->DeactivateAll();
	}

	template<class componentStruct>
	void ComponentManager::Delete(int componentId)
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());
		assert(foundIt->second.has_value());

		std::any_cast<ComponentPool<componentStruct>>(&foundIt->second)->Deactivate(componentId);
	}

	template<class componentStruct>
	const std::unordered_set<FreeListPoolElement<componentStruct>*>& ComponentManager::GetComponents()
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());
		assert(foundIt->second.has_value());

		return std::any_cast<ComponentPool<componentStruct>>(&foundIt->second)->GetActiveElements();
	}

	template<class componentStruct>
	bool ComponentManager::IsContainAvailablePlace() const
	{
		EComponentType type = componentStruct::GetType();

		auto foundIt = m_componentsPools.find(type);
		assert(foundIt != m_componentsPools.end());
		assert(foundIt->second.has_value());

		return std::any_cast<ComponentPool<componentStruct>>(&foundIt->second)->IsContainAvailablePlace();
	}
}