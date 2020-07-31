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

		virtual void* Allocate(const size_t size) = 0;
		virtual void Deallocate(void* p) = 0;

	protected:

		size_t m_memorySize = 0;
		size_t m_allocatedMemorySize = 0;
		size_t m_allocationsNumber = 0;
		size_t m_deallocatedMemorySize = 0;
		size_t m_deallocationsNumber = 0;
	};

	template<typename T, typename... Args>
	T* Allocate(Allocator* allocator, Args& ... args)
	{
		return new (allocator->Allocate(sizeof(T))) T(args...);
	};

	template<typename T>
	void Deallocate(Allocator* allocator, T* object)
	{
		object->~T();

		allocator->Deallocate(static_cast<void*>(object));
	};
}