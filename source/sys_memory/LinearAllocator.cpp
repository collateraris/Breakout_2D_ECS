#include <LinearAllocator.h>

#include <cassert>

using namespace breakout;

LinearAllocator::LinearAllocator(const size_t size)
    : Allocator(size)
{
    m_memoryStart = static_cast<void*>(new uint8_t[size]);
    m_currentPosition = m_memoryStart;
}

LinearAllocator::~LinearAllocator()
{
    Clear();
    delete[] m_memoryStart;
}

void* LinearAllocator::Allocate(const size_t size)
{
    assert(size > 0);

    const size_t additionalSize = sizeof(size_t);
    assert(m_allocatedMemorySize + size + additionalSize < m_memorySize);

    size_t* prevCurrentPosition = static_cast<size_t*>(m_currentPosition);
    *prevCurrentPosition = size;
    ++prevCurrentPosition;

    const size_t currentOffset = additionalSize + size;

    m_currentPosition = static_cast<void*>(static_cast<uint8_t*>(m_currentPosition) + currentOffset);

    m_allocatedMemorySize += currentOffset;
    ++m_allocationsNumber;

    return static_cast<void*>(prevCurrentPosition);
}

void LinearAllocator::Deallocate(void* p)
{
    assert(p);
    assert(p > m_memoryStart);
    assert(p < (static_cast<uint8_t*>(m_memoryStart) + m_memorySize));

    const size_t size = static_cast<size_t*>(p)[-1];
    const size_t additionalSize = sizeof(size_t);

    m_deallocatedMemorySize += additionalSize + size;
    ++m_deallocationsNumber;
}

void LinearAllocator::Clear()
{
    assert(m_allocationsNumber == m_deallocationsNumber);
    assert(m_allocatedMemorySize = m_deallocatedMemorySize);

    m_memorySize = 0;
    m_allocatedMemorySize = 0;
    m_allocationsNumber = 0;
    m_deallocatedMemorySize = 0;
    m_deallocationsNumber = 0;

    m_currentPosition = m_memoryStart;
}