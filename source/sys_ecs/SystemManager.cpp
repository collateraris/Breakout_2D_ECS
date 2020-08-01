#include <SystemManager.h>

using namespace breakout;

SystemManager::SystemManager()
{
	
}

SystemManager::~SystemManager()
{
	Reset();
}

SystemManager& SystemManager::Get()
{
	static SystemManager systemManager;
	return systemManager;
}

void SystemManager::Reset()
{
	auto globalAllocator = MemoryManager::Get().GetGlobalAllocator();

	for (auto& systemIt: m_systems)
	{
		Deallocate(globalAllocator.get(), systemIt.second);
	}

	m_systems.clear();
}