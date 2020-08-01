#pragma once

#include <LinearAllocator.h>

#include <memory>

namespace breakout
{
	class MemoryManager
	{
	public:

		static MemoryManager& Get();

		std::shared_ptr<LinearAllocator> GetGlobalAllocator() const;

	private:

		MemoryManager();
		~MemoryManager();
		MemoryManager(MemoryManager&) = delete;
		MemoryManager(MemoryManager&&) = delete;
		void operator=(MemoryManager&) = delete;
		void operator=(MemoryManager&&) = delete;

		std::shared_ptr<LinearAllocator> m_globalAllocator;
	};
}