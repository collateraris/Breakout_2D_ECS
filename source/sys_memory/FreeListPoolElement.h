#pragma once

#include <FreeListObjectPool.h>

#include <variant>

namespace breakout
{
	template<class containerStruct>
	class FreeListPoolElement
	{
	public:

		FreeListPoolElement();
		~FreeListPoolElement() = default;

		bool IsActive() const;

		void SetContainer(const containerStruct& container);

		containerStruct& GetContainer();

	private:

		friend class FreeListObjectPool<FreeListPoolElement<containerStruct>>;

		FreeListPoolElement<containerStruct>* GetNext();

		void SetNext(FreeListPoolElement<containerStruct>* next);

		void Activate();

		void Deactivate();

		std::variant<containerStruct, FreeListPoolElement<containerStruct>*> m_container, m_next;

		bool b_active = false;
	};

	template<class containerStruct>
	FreeListPoolElement<containerStruct>::FreeListPoolElement()
	{

	}

	template<class containerStruct>
	FreeListPoolElement<containerStruct>* FreeListPoolElement<containerStruct>::GetNext()
	{
		return std::get<FreeListPoolElement<containerStruct>*>(m_next);
	}

	template<class containerStruct>
	void FreeListPoolElement<containerStruct>::SetNext(FreeListPoolElement<containerStruct>* next)
	{
		m_next = next;
	}

	template<class containerStruct>
	void FreeListPoolElement<containerStruct>::Activate()
	{
		b_active = true;
	}

	template<class containerStruct>
	void FreeListPoolElement<containerStruct>::Deactivate()
	{
		b_active = false;
	}

	template<class containerStruct>
	bool FreeListPoolElement<containerStruct>::IsActive() const
	{
		return b_active;
	}

	template<class containerStruct>
	void FreeListPoolElement<containerStruct>::SetContainer(const containerStruct& container)
	{
		m_container = container;
	}

	template<class containerStruct>
	containerStruct& FreeListPoolElement<containerStruct>::GetContainer()
	{
		return std::get<containerStruct>(m_container);
	}
}