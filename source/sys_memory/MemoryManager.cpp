#include <MemoryManager.h>

using namespace breakout;

constexpr size_t GLOBAL_POOL_SIZE = sizeof(size_t) * 10000;

MemoryManager::MemoryManager()
{
	m_globalAllocator = std::make_shared<LinearAllocator>(GLOBAL_POOL_SIZE);
}

MemoryManager::~MemoryManager()
{

}

MemoryManager& MemoryManager::Get()
{
	static MemoryManager memoryManager;
	return memoryManager;
}

std::shared_ptr<LinearAllocator> MemoryManager::GetGlobalAllocator() const
{
	return m_globalAllocator;
}