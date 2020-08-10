#pragma once

#include <EventType.h>

#include <vector>
#include <unordered_map>

namespace breakout
{
	class EventsStorage
	{
	public:

		static EventsStorage& Get();

		void Init();

		void Put(BaseEvent& event);

		std::vector<BaseEvent>& GetAll(EEventType eventTypeEnum);

		bool IsContain(EEventType eventTypeEnum);

		void SwapStorages();

	protected:


		void ClearInactiveStorage();

	private:

		EventsStorage();
		~EventsStorage();
		EventsStorage(EventsStorage&) = delete;
		EventsStorage(EventsStorage&&) = delete;
		void operator=(EventsStorage&) = delete;
		void operator=(EventsStorage&&) = delete;

		bool m_active_storage_index = 0;
		std::unordered_map<EEventType, std::vector<BaseEvent>> m_storage[2];
	};
}