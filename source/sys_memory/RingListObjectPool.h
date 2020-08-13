#pragma once

#include <array>
#include <cassert>

namespace breakout
{
	template<class containerStruct, size_t sizeArr>
	class RingListObjectPool
	{
	public:

		RingListObjectPool();
		~RingListObjectPool();

		unsigned int GetNextElementIndex();
		containerStruct& Next();
		containerStruct& GetElement(unsigned int i);

		std::array<containerStruct, sizeArr>& GetPoolElements();

	private:

		unsigned int m_poolSize;
		unsigned int m_nextElement = 0;

		std::array<containerStruct, sizeArr> m_poolObjects;
	};

	template<class containerStruct, unsigned int sizeArr>
	RingListObjectPool<containerStruct, sizeArr>::RingListObjectPool()
	{
		m_poolSize = m_poolObjects.size();
	}

	template<class containerStruct, unsigned int sizeArr>
	RingListObjectPool<containerStruct, sizeArr>::~RingListObjectPool()
	{

	}

	template<class containerStruct, unsigned int sizeArr>
	unsigned int RingListObjectPool<containerStruct, sizeArr>::GetNextElementIndex()
	{
		return m_nextElement;
	}

	template<class containerStruct, unsigned int sizeArr>
	containerStruct& RingListObjectPool<containerStruct, sizeArr>::Next()
	{
		containerStruct& container = m_poolObjects[m_nextElement];
		m_nextElement = (++m_nextElement) >= m_poolSize ? 0 : m_nextElement;
		return container;
	}

	template<class containerStruct, unsigned int sizeArr>
	containerStruct& RingListObjectPool<containerStruct, sizeArr>::GetElement(unsigned int i)
	{
		assert(i < m_poolSize);
		return m_poolObjects[i];
	}

	template<class containerStruct, unsigned int sizeArr>
	std::array<containerStruct, sizeArr>& RingListObjectPool<containerStruct, sizeArr>::GetPoolElements()
	{
		return m_poolObjects;
	}
}