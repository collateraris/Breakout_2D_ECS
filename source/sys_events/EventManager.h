#pragma once

#include <Delegate.h>


namespace breakout
{
	class ColliderComponent;

	class EventManager
	{

	public:

		static EventManager& Get();

		MulticastDelegate<const ColliderComponent&, const ColliderComponent&>& OnCollitionDetected();
		MulticastDelegate<>& OnNewLevelLoaded();
		MulticastDelegate<>& OnGameEnded();

	private:

		EventManager();
		~EventManager();
		EventManager(EventManager&) = delete;
		EventManager(EventManager&&) = delete;
		void operator=(EventManager&) = delete;
		void operator=(EventManager&&) = delete;

		MulticastDelegate<const ColliderComponent&, const ColliderComponent&> OnCollitionDetectedDelegate;
		MulticastDelegate<> OnNewLevelLoadedDelegate;
		MulticastDelegate<> OnGameEndedDelegate;
	};
}

