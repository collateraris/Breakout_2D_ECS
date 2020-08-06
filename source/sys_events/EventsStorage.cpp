#include <EventsStorage.h>

#include <cassert>

using namespace breakout;

EventsStorage::EventsStorage()
{

}

EventsStorage::~EventsStorage()
{

}

EventsStorage& EventsStorage::Get()
{
	static EventsStorage eventStorage;
	return eventStorage;
}

void EventsStorage::Init()
{

}

void EventsStorage::Put(BaseEvent& event)
{
	EEventType eventType = event.GetType();
	if (IsContain(eventType))
	{
		m_storage[!m_active_storage_index][eventType].emplace_back(event);
	}
	else
	{
		m_storage[!m_active_storage_index][eventType] = std::move(std::vector<BaseEvent>({ event }));
	}
}

std::vector<BaseEvent>& EventsStorage::GetAll(EEventType eventTypeEnum)
{
	assert(IsContain(eventTypeEnum)
		&& "There is no current event, use IsContain to check it before");

	return m_storage[m_active_storage_index][eventTypeEnum];
}

bool EventsStorage::IsContain(EEventType eventTypeEnum)
{
	auto currentEventIds = m_storage[m_active_storage_index].find(eventTypeEnum);

	return currentEventIds != m_storage[m_active_storage_index].end();
}

void EventsStorage::SwapStorages()
{
	m_active_storage_index = !m_active_storage_index;

	ClearInactiveStorage();
}

void EventsStorage::ClearInactiveStorage()
{
	for (auto& inactiveEvents : m_storage[!m_active_storage_index])
	{
		inactiveEvents.second.clear();
	}
}