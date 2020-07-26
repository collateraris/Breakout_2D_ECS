#include <gameContext.h>

#include <gameWindow.h>

using namespace breakout;

GameContext* GameContext::m_gameContext;

GameContext::GameContext()
{
	m_mainWindow = new GameWindow();
}

GameContext::~GameContext()
{
	delete m_mainWindow;
}

GameContext& GameContext::Get()
{
	static GameContext context;
	return context;
}

GameWindow* GameContext::GetMainWindow()
{
	return m_mainWindow;
}