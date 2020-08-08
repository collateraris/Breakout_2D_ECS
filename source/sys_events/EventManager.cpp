#include <EventManager.h>

using namespace breakout;

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

EventManager& EventManager::Get()
{
	static EventManager eventManager;
	return eventManager;
}

MulticastDelegate<EventManager::entityId, EventManager::entityId>& EventManager::OnCollitionDetected()
{
	return OnCollitionDetectedDelegate;
}