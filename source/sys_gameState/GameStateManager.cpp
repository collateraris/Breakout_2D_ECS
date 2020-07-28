#include <GameStateManager.h>

#include <gameContext.h>
#include <EventsStorage.h>
#include <LogManager.h>

#include <cassert>

using namespace breakout;

GameStateManager::GameStateManager()
{

}

GameStateManager::~GameStateManager()
{

}

GameStateManager& GameStateManager::Get()
{
	static GameStateManager gameStateManager;
	return gameStateManager;
}

void GameStateManager::Init()
{

}

void GameStateManager::SwitchState(EGameState newState)
{
	EGameState prevState = m_currentState;
	assert(IsPossibleToChangeState(newState) && "You can't go to this state from current");

	auto gameStateChangeEventObj = GameStateChangeEvent(EEventType::GAME_STATE_CHANGE, prevState, newState);
	GameContext::Get().GetEventsStorage().Put(gameStateChangeEventObj);

	m_currentState = newState;

	LOG("Game State changed from " + ConvertGameStateToString(prevState) + " to " + ConvertGameStateToString(newState));
}

EGameState GameStateManager::GetCurrentState() const
{
	return m_currentState;
}

bool GameStateManager::IsPossibleToChangeState(EGameState newState) const
{
	switch (m_currentState) // Here shown all of the possible transitions
	{
	case EGameState::IDLE:
		return true;
	case EGameState::MAIN_MENU:
		return newState == EGameState::GAME || newState == EGameState::CLOSE_APP || newState == EGameState::IDLE;
		break;
	case EGameState::PAUSE:
		return newState == EGameState::MAIN_MENU || newState == EGameState::GAME || newState == EGameState::CLOSE_APP;
		break;
	case EGameState::GAME:
		return newState == EGameState::GAME_OVER || newState == EGameState::PAUSE || newState == EGameState::CLOSE_APP;
		break;
	case EGameState::GAME_OVER:
		return newState == EGameState::MAIN_MENU || newState == EGameState::CLOSE_APP;
		break;
	default:
		return false;
		break;
	}
}

std::string GameStateManager::ConvertGameStateToString(EGameState gameState)
{
	static const std::string idleStr = "IDLE";
	static const std::string mainMenuStr = "MAIN_MENU";
	static const std::string pauseStr = "PAUSE";
	static const std::string gameStr = "GAME";
	static const std::string closeAppStr = "CLOSE_APP";
	static const std::string gameOverStr = "GAME_OVER";

	switch(gameState)
	{
	case EGameState::IDLE: return idleStr;
		break;
	case EGameState::MAIN_MENU: return mainMenuStr;
		break;
	case EGameState::PAUSE: return pauseStr;
		break;
	case EGameState::GAME: return gameStr;
		break;
	case EGameState::CLOSE_APP: return closeAppStr;
		break;
	case EGameState::GAME_OVER: return gameOverStr;
		break;
	default:
		return "";
	}

}

