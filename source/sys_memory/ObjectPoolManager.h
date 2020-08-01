#pragma once

namespace breakout
{
	class ObjectPoolManager
	{
	public:

		static ObjectPoolManager& Get();

	private:

		ObjectPoolManager();
		~ObjectPoolManager();
		ObjectPoolManager(ObjectPoolManager&) = delete;
		ObjectPoolManager(ObjectPoolManager&&) = delete;
		void operator=(ObjectPoolManager&) = delete;
		void operator=(ObjectPoolManager&&) = delete;
	};
}