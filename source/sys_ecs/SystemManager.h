#pragma once

#include <System.h>

#include <MemoryManager.h>

#include <memory>
#include <unordered_map>

namespace breakout
{
	class SystemManager
	{
	public:

		static SystemManager& Get();

		template<typename systemClass>
		systemClass* CreateSystem();

		template<typename systemClass>
		BaseSystem* GetSystem();

		void Reset();

	private:

		SystemManager();
		~SystemManager();
		SystemManager(SystemManager&) = delete;
		SystemManager(SystemManager&&) = delete;
		void operator=(SystemManager&) = delete;
		void operator=(SystemManager&&) = delete;

		std::unordered_map<EBaseSystemType, BaseSystem*> m_systems;

	};

	template<typename systemClass>
	systemClass* SystemManager::CreateSystem()
	{
		static_assert(std::is_base_of<BaseSystem, systemClass>::value
			, "Element must be a descendant of BaseSystem");


		EBaseSystemType type = systemClass::GetType();
		auto foundIt = m_systems.find(type);
		assert(foundIt == m_systems.end());

		auto globalAllocator = MemoryManager::Get().GetGlobalAllocator();
		auto system = allocate<systemClass>(globalAllocator.get());

		m_systems[type] = system;

		return system;
	}

	template<typename systemClass>
	BaseSystem* SystemManager::GetSystem()
	{
		static_assert(std::is_base_of<BaseSystem, systemClass>::value
			, "Element must be a descendant of BaseSystem");

		EBaseSystemType type = systemClass::GetType();
		auto foundIt = m_systems.find(type);
		assert(foundIt != m_systems.end());

		return foundIt->second;
	}
}