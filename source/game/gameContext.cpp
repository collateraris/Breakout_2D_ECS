#include <gameContext.h>

#include <gameWindow.h>

using namespace breakout;

GameContext* GameContext::m_gameContext;

GameContext::GameContext()
{
	m_mainWindow = std::make_shared<GameWindow>();
}

GameContext::~GameContext()
{
}

GameContext& GameContext::Get()
{
	static GameContext context;
	return context;
}

std::shared_ptr<GameWindow>& GameContext::GetMainWindow()
{
	return m_mainWindow;
}