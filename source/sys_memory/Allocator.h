#pragma once

#include <cassert>
#include <functional>

namespace breakout
{
	class Allocator
	{
	public:

		Allocator(const size_t size);
		virtual ~Allocator() = 0;

		virtual void* allocate(const size_t size) = 0;
		virtual void deallocate(void* p) = 0;

	protected:

		size_t m_memorySize = 0;
		size_t m_allocatedMemorySize = 0;
		size_t m_allocationsNumber = 0;
		size_t m_deallocatedMemorySize = 0;
		size_t m_deallocationsNumber = 0;
	};

	template<typename T, typename... Args>
	T* allocate(Allocator* allocator, Args& ... args)
	{
		return new (allocator->allocate(sizeof(T))) T(args...);
	};

	template<typename T>
	void deallocate(Allocator* allocator, T* object)
	{
		object->~T();

		allocator->deallocate(static_cast<void*>(object));
	};
}