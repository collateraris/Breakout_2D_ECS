#pragma once

namespace breakout
{
	enum class EEventType
	{
		GAME_STATE_CHANGE,
        PLAYER_ACTION_MOVE_LEFT,
        PLAYER_ACTION_MOVE_RIGHT,
		MAX
	};

    class BaseEvent
    {
    public:
        BaseEvent(EEventType eventType)
            : m_eventType(eventType) {}

        virtual ~BaseEvent() {};

        EEventType GetType() const
        {
            return m_eventType;
        }

    private:

        EEventType m_eventType;
    };

}