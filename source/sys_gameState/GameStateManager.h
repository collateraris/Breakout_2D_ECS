#pragma once

#include <EventType.h>

#include <string>

namespace breakout
{
	enum struct EGameState
	{
		IDLE,
		MAIN_MENU,
		GAME,
		PAUSE,
		CLOSE_APP,
		GAME_OVER,
	};

	class GameStateChangeEvent : public BaseEvent
	{
	public:
		EGameState mPrevState;
		EGameState mNewState;

		GameStateChangeEvent(EEventType eventType, EGameState prevState, EGameState newState)
			: BaseEvent::BaseEvent(eventType)
			, mPrevState(prevState)
			, mNewState(newState)
		{};

		~GameStateChangeEvent()
		{};

	};

	class GameStateManager
	{
	public:

		static GameStateManager& Get();

		void Init();

		void SwitchState(EGameState newState);

		EGameState GetCurrentState() const;

		static std::string ConvertGameStateToString(EGameState gameState);

	protected:

		bool IsPossibleToChangeState(EGameState newState) const;

	private:

		GameStateManager();
		~GameStateManager();
		GameStateManager(GameStateManager&) = delete;
		GameStateManager(GameStateManager&&) = delete;
		void operator=(GameStateManager&) = delete;
		void operator=(GameStateManager&&) = delete;

		EGameState m_currentState = EGameState::MAIN_MENU;
	};
}