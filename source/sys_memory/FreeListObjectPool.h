#pragma once

#include <vector>
#include <cassert>

namespace breakout
{
	template<typename freeListPoolElement>
	class FreeListObjectPool
	{
	public:

		FreeListObjectPool(unsigned int poolSize);
		~FreeListObjectPool() = default;

		freeListPoolElement& Activate();

		void Deactivate(unsigned int poolIndex);

		void DeactivateAll();

		unsigned int GetPoolSize() const;

		freeListPoolElement& GetPoolElement(unsigned int poolIndex);

		bool IsContainAvailablePlace() const;

	private:

		unsigned int m_poolSize;

		freeListPoolElement* m_firstAvailable = nullptr;

		std::vector<freeListPoolElement> m_poolElements = {};
	};

	template<typename freeListPoolElement>
	FreeListObjectPool<freeListPoolElement>::FreeListObjectPool(unsigned int poolSize)
	{
		m_poolSize = poolSize;

		m_poolElements.resize(poolSize, {});

		m_firstAvailable = &m_poolElements[0];

		for (unsigned int i = 0; i < poolSize - 1; ++i)
		{
			m_poolElements[i].SetNext(&m_poolElements[i + 1]);
		}

		m_poolElements[poolSize - 1].SetNext(nullptr);
	}

	template<typename freeListPoolElement>
	freeListPoolElement& FreeListObjectPool<freeListPoolElement>::Activate()
	{
		assert(m_firstAvailable != nullptr);

		freeListPoolElement* newElement = m_firstAvailable;
		m_firstAvailable = newElement->GetNext();

		newElement->Activate();

		return *newElement;
	}

	template<typename freeListPoolElement>
	void FreeListObjectPool<freeListPoolElement>::Deactivate(unsigned int poolIndex)
	{
		assert(poolIndex < m_poolSize);
		assert(m_poolElements[poolIndex].IsActive());

		m_poolElements[poolIndex].SetNext(m_firstAvailable);
		m_firstAvailable = &m_poolElements[poolIndex];

		m_poolElements[poolIndex].Deactivate();
	}

	template<typename freeListPoolElement>
	void FreeListObjectPool<freeListPoolElement>::DeactivateAll()
	{
		for (unsigned int i = 0; i < m_poolSize; ++i)
		{
			if (!m_poolElements[i].IsActive())
				continue;
			Deactivate(i);
		}
	}

	template<typename freeListPoolElement>
	unsigned int FreeListObjectPool<freeListPoolElement>::GetPoolSize() const
	{
		return m_poolSize;
	}

	template<typename freeListPoolElement>
	freeListPoolElement& FreeListObjectPool<freeListPoolElement>::GetPoolElement(unsigned int poolIndex)
	{
		assert(poolIndex < m_poolSize);
		return m_poolElements[poolIndex];
	}

	template<typename freeListPoolElement>
	bool FreeListObjectPool<freeListPoolElement>::IsContainAvailablePlace() const
	{
		return m_firstAvailable != nullptr;
	}
}