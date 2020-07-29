#include <MemoryManager.h>

using namespace breakout;

MemoryManager::MemoryManager()
{

}

MemoryManager::~MemoryManager()
{

}

MemoryManager& MemoryManager::Get()
{
	static MemoryManager memoryManager;
	return memoryManager;
}