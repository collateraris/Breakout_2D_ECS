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
#include <RenderSystem.h>
#include <MovementSystem.h>
#include <GameplaySystem.h>
#include <PhysicsSystem.h>

using namespace breakout;

GameContext::GameContext()
{
	m_mainWindow = std::make_shared<GameWindow>();

	m_renderSystem = SystemManager::Get().CreateSystem<RenderSystem>();
	m_movementSystem = SystemManager::Get().CreateSystem<MovementSystem>();
	m_gameplaySystem = SystemManager::Get().CreateSystem<GameplaySystem>();
	m_physicsSystem = SystemManager::Get().CreateSystem<PhysicsSystem>();
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

RenderSystem* GameContext::GetRenderSystem()
{
	return m_renderSystem;
}

MovementSystem* GameContext::GetMovementSystem()
{
	return m_movementSystem;
}

GameplaySystem* GameContext::GetGameplaySystem()
{
	return m_gameplaySystem;
}

PhysicsSystem* GameContext::GetPhysicsSystem()
{
	return m_physicsSystem;
}

void GameContext::GetMainWindowSize(int& w, int& h)
{
	w = m_mainWindow->GetWidth();
	h = m_mainWindow->GetHeight();
}