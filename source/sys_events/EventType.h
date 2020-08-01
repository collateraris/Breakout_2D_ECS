#pragma once

namespace breakout
{
	enum class EEventType
	{
		GAME_STATE_CHANGE,
		MAX
	};

    class BaseEvent
    {
    public:
        BaseEvent(EEventType eventType)
            : m_eventType(eventType) {}

        ~BaseEvent() {};

        EEventType GetType() const
        {
            return m_eventType;
        }

    private:

        EEventType m_eventType;
    };
}