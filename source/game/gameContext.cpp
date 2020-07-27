#include <gameContext.h>

#include <gameWindow.h>
#include <ConfigManager.h>
#include <LogManager.h>

using namespace breakout;

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

ConfigManager& GameContext::GetConfigManager()
{
	return ConfigManager::Get();
}

LogManager& GameContext::GetLogManager()
{
	return LogManager::Get();
}