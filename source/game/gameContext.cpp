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
#include <SystemManager.h>
#include <SpriteRenderSystem.h>
#include <InputSystem.h>
#include <MovementSystem.h>

using namespace breakout;

GameContext::GameContext()
{
	m_mainWindow = std::make_shared<GameWindow>();

	m_spriteRenderSystem = SystemManager::Get().CreateSystem<SpriteRenderSystem>();
	m_movementSystem = SystemManager::Get().CreateSystem<MovementSystem>();
	m_inputSystem = SystemManager::Get().CreateSystem<InputSystem>();
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

SpriteRenderSystem* GameContext::GetSpriteRenderSystem()
{
	return m_spriteRenderSystem;
}

MovementSystem* GameContext::GetMovementSystem()
{
	return m_movementSystem;
}

InputSystem* GameContext::GetInputSystem()
{
	return m_inputSystem;
}