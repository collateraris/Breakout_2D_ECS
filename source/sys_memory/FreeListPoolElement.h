#pragma once

#include <variant>

namespace breakout
{
	template<typename liveStruct>
	class FreeListPoolElement
	{
	public:

		FreeListPoolElement();
		~FreeListPoolElement() = default;

		FreeListPoolElement<liveStruct>* GetNext();

		void SetNext(FreeListPoolElement<liveStruct>* next);

	private:

		std::variant<liveStruct, FreeListPoolElement<liveStruct>*> m_live, m_next;
	};

	template<typename liveStruct>
	FreeListPoolElement<liveStruct>::FreeListPoolElement()
	{

	}

	template<typename liveStruct>
	FreeListPoolElement<liveStruct>* FreeListPoolElement<liveStruct>::GetNext()
	{
		return m_next;
	}

	template<typename liveStruct>
	void FreeListPoolElement<liveStruct>::SetNext(FreeListPoolElement<liveStruct>* next)
	{
		m_next = next;
	}

	struct PoolTestLive
	{
		int a = 0;
	};

	class PoolTestElement : public FreeListPoolElement<PoolTestLive>
	{
	public:

		PoolTestElement() : FreeListPoolElement<PoolTestLive>(){};
		~PoolTestElement() = default;
	};
}