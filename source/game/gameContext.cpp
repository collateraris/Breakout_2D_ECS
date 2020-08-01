#include <gameContext.h>

#include <gameWindow.h>
#include <ConfigManager.h>
#include <LogManager.h>
#include <GameStateManager.h>
#include <EventsStorage.h>
#include <MemoryManager.h>
#include <SystemManager.h>
#include <AssetsManager.h>

#include <EntityComponentSystem.h>

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

GameStateManager& GameContext::GetGameStateManager()
{
	return GameStateManager::Get();
}

AssetManager& GameContext::GetAssetManager()
{
	return AssetManager::Get();
}

EventsStorage& GameContext::GetEventsStorage()
{
	return EventsStorage::Get();
}

MemoryManager& GameContext::GetMemoryManager()
{
	return MemoryManager::Get();
}

SystemManager& GameContext::GetSystemManager()
{
	return SystemManager::Get();
}

EntityComponentSystem& GameContext::GetECS()
{
	return EntityComponentSystem::Get();
}