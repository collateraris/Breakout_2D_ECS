#pragma once

#include <vector>
#include <unordered_set>
#include <cassert>

namespace breakout
{
	template<class freeListPoolElement>
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

		const std::vector<freeListPoolElement>& GetPoolElements();

		const std::unordered_set<freeListPoolElement*>& GetActiveElements();

		bool IsContainAvailablePlace() const;

	private:

		unsigned int m_poolSize = 0;

		freeListPoolElement* m_firstAvailable = nullptr;

		std::vector<freeListPoolElement> m_poolElements = {};

		std::unordered_set<freeListPoolElement*> m_activeElements = {};
	};

	template<class freeListPoolElement>
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

	template<class freeListPoolElement>
	freeListPoolElement& FreeListObjectPool<freeListPoolElement>::Activate()
	{
		assert(m_firstAvailable != nullptr);

		freeListPoolElement* newElement = m_firstAvailable;
		m_firstAvailable = newElement->GetNext();

		newElement->Activate();

		m_activeElements.insert(newElement);

		return *newElement;
	}

	template<class freeListPoolElement>
	void FreeListObjectPool<freeListPoolElement>::Deactivate(unsigned int poolIndex)
	{
		assert(poolIndex < m_poolSize);
		assert(m_poolElements[poolIndex].IsActive());

		m_poolElements[poolIndex].SetNext(m_firstAvailable);
		m_firstAvailable = &m_poolElements[poolIndex];

		m_poolElements[poolIndex].Deactivate();

		m_activeElements.erase(&m_poolElements[poolIndex]);
	}

	template<class freeListPoolElement>
	void FreeListObjectPool<freeListPoolElement>::DeactivateAll()
	{
		m_firstAvailable = &m_poolElements[0];

		for (unsigned int i = 0; i < poolSize - 1; ++i)
		{
			m_poolElements[i].SetNext(&m_poolElements[i + 1]);
			m_poolElements[i].Deactivate();
		}

		m_poolElements[poolSize - 1].SetNext(nullptr);
		m_poolElements[poolSize - 1].Deactivate();

		m_activeElements.clear();
	}

	template<class freeListPoolElement>
	unsigned int FreeListObjectPool<freeListPoolElement>::GetPoolSize() const
	{
		return m_poolSize;
	}

	template<class freeListPoolElement>
	freeListPoolElement& FreeListObjectPool<freeListPoolElement>::GetPoolElement(unsigned int poolIndex)
	{
		assert(poolIndex < m_poolSize);
		return m_poolElements[poolIndex];
	}

	template<class freeListPoolElement>
	const std::vector<freeListPoolElement>& FreeListObjectPool<freeListPoolElement>::GetPoolElements()
	{
		return m_poolElements;
	}

	template<class freeListPoolElement>
	const std::unordered_set<freeListPoolElement*>& FreeListObjectPool<freeListPoolElement>::GetActiveElements()
	{
		return m_activeElements;
	}

	template<class freeListPoolElement>
	bool FreeListObjectPool<freeListPoolElement>::IsContainAvailablePlace() const
	{
		return m_firstAvailable != nullptr;
	}
}