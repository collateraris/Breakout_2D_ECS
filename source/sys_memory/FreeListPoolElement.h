#pragma once

#include <FreeListObjectPool.h>

#include <variant>

namespace breakout
{
	template<typename liveStruct>
	class FreeListPoolElement
	{
	public:

		FreeListPoolElement();
		~FreeListPoolElement() = default;

		bool IsActive();

		void SetLive(const liveStruct live);

	private:

		friend class FreeListObjectPool<FreeListPoolElement<liveStruct>>;

		FreeListPoolElement<liveStruct>* GetNext();

		void SetNext(FreeListPoolElement<liveStruct>* next);

		void Activate();

		void Deactivate();

		std::variant<liveStruct, FreeListPoolElement<liveStruct>*> m_live, m_next;

		bool b_active = false;
	};

	template<typename liveStruct>
	FreeListPoolElement<liveStruct>::FreeListPoolElement()
	{

	}

	template<typename liveStruct>
	FreeListPoolElement<liveStruct>* FreeListPoolElement<liveStruct>::GetNext()
	{
		return std::get<FreeListPoolElement<liveStruct>*>(m_next);
	}

	template<typename liveStruct>
	void FreeListPoolElement<liveStruct>::SetNext(FreeListPoolElement<liveStruct>* next)
	{
		m_next = next;
	}

	template<typename liveStruct>
	void FreeListPoolElement<liveStruct>::Activate()
	{
		b_active = true;
	}

	template<typename liveStruct>
	void FreeListPoolElement<liveStruct>::Deactivate()
	{
		b_active = false;
	}

	template<typename liveStruct>
	bool FreeListPoolElement<liveStruct>::IsActive()
	{
		return b_active;
	}

	template<typename liveStruct>
	void FreeListPoolElement<liveStruct>::SetLive(const liveStruct live)
	{
		m_live = live;
	}

}