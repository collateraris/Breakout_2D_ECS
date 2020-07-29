#pragma once

namespace breakout
{
	class MemoryManager
	{
	public:

		static MemoryManager& Get();

	private:

		MemoryManager();
		~MemoryManager();
		MemoryManager(MemoryManager&) = delete;
		MemoryManager(MemoryManager&&) = delete;
		void operator=(MemoryManager&) = delete;
		void operator=(MemoryManager&&) = delete;
	};
}