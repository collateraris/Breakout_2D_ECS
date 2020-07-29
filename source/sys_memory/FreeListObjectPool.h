#pragma once

#include <vector>

namespace breakout
{
	template<typename freeListPoolElement>
	class FreeListObjectPool
	{
	public:

		FreeListObjectPool(unsigned int poolSize);
		~FreeListObjectPool() = default;

	private:

		freeListPoolElement* m_firstAvailable = nullptr;

		std::vector<freeListPoolElement> m_poolElements = {};
	};

	template<typename freeListPoolElement>
	FreeListObjectPool<freeListPoolElement>::FreeListObjectPool(unsigned int poolSize)
	{
		m_poolElements.resize(poolSize, {});

		m_firstAvailable = &m_poolElements[0];

		for (unsigned int i = 0; i < poolSize - 1; ++i)
		{
			m_poolElements[i].SetNext(&m_poolElements[i + 1]);
		}

		m_poolElements[poolSize - 1].SetNext(nullptr);
	}

}