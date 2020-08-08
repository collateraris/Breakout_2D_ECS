#pragma once

#include <Delegate.h>

namespace breakout
{
	class EventManager
	{
		using entityId = int;

	public:

		static EventManager& Get();

		MulticastDelegate<entityId, entityId>& OnCollitionDetected();

	private:

		EventManager();
		~EventManager();
		EventManager(EventManager&) = delete;
		EventManager(EventManager&&) = delete;
		void operator=(EventManager&) = delete;
		void operator=(EventManager&&) = delete;

		MulticastDelegate<entityId, entityId> OnCollitionDetectedDelegate;
	};
}

