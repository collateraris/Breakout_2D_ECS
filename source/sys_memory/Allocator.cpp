#include <Allocator.h>

using namespace breakout;

Allocator::Allocator(const size_t size)
	: m_memorySize{ size }
{
	assert(size > 0);
};

Allocator::~Allocator()
{
	assert(m_allocationsNumber == m_deallocationsNumber);
	assert(m_allocatedMemorySize == m_deallocatedMemorySize);
}

