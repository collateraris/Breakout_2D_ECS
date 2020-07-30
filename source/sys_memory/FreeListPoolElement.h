#pragma once

#include <FreeListObjectPool.h>

#include <variant>

namespace breakout
{
	template<class liveStruct>
	class FreeListPoolElement
	{
	public:

		FreeListPoolElement();
		~FreeListPoolElement() = default;

		bool IsActive();

		void SetLive(const liveStruct live);

		liveStruct& GetLive();

	private:

		friend class FreeListObjectPool<FreeListPoolElement<liveStruct>>;

		FreeListPoolElement<liveStruct>* GetNext();

		void SetNext(FreeListPoolElement<liveStruct>* next);

		void Activate();

		void Deactivate();

		std::variant<liveStruct, FreeListPoolElement<liveStruct>*> m_live, m_next;

		bool b_active = false;
	};

	template<class liveStruct>
	FreeListPoolElement<liveStruct>::FreeListPoolElement()
	{

	}

	template<class liveStruct>
	FreeListPoolElement<liveStruct>* FreeListPoolElement<liveStruct>::GetNext()
	{
		return std::get<FreeListPoolElement<liveStruct>*>(m_next);
	}

	template<class liveStruct>
	void FreeListPoolElement<liveStruct>::SetNext(FreeListPoolElement<liveStruct>* next)
	{
		m_next = next;
	}

	template<class liveStruct>
	void FreeListPoolElement<liveStruct>::Activate()
	{
		b_active = true;
	}

	template<class liveStruct>
	void FreeListPoolElement<liveStruct>::Deactivate()
	{
		b_active = false;
	}

	template<class liveStruct>
	bool FreeListPoolElement<liveStruct>::IsActive()
	{
		return b_active;
	}

	template<class liveStruct>
	void FreeListPoolElement<liveStruct>::SetLive(const liveStruct live)
	{
		m_live = live;
	}

	template<class liveStruct>
	liveStruct& FreeListPoolElement<liveStruct>::GetLive()
	{
		return std::get<liveStruct>(m_live);
	}
}