#include <EventManager.h>

#include <ColliderComponent.h>

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

MulticastDelegate<const ColliderComponent&, const ColliderComponent&>& EventManager::OnCollitionDetected()
{
	return OnCollitionDetectedDelegate;
}

MulticastDelegate<>& EventManager::OnNewLevelLoaded()
{
	return OnNewLevelLoadedDelegate;
}