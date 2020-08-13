#pragma once

#ifdef _DEBUG
#define LOG(...) breakout::GameContext::Get().GetLogManager().Log(__VA_ARGS__)
#else
#define LOG(...) 
#endif // _DEBUG

#include <memory>

namespace breakout
{

	class GameWindow;
	class ConfigManager;
	class LogManager;
	class GameStateManager;
	class EventsStorage;
	class MemoryManager;
	class SystemManager;
	class EntityComponentSystem;
	class AssetManager;

	class RenderSystem;
	class MovementSystem;
	class GameplaySystem;
	class PhysicsSystem;

	class GameContext
	{
	public:

		static GameContext& Get();

		std::shared_ptr<GameWindow>& GetMainWindow();

		ConfigManager& GetConfigManager();
		LogManager& GetLogManager();
		GameStateManager& GetGameStateManager();
		MemoryManager& GetMemoryManager();
		SystemManager& GetSystemManager();
		AssetManager& GetAssetManager();

		EventsStorage& GetEventsStorage();

		EntityComponentSystem& GetECS();

		RenderSystem* GetRenderSystem();
		MovementSystem* GetMovementSystem();
		GameplaySystem* GetGameplaySystem();
		PhysicsSystem* GetPhysicsSystem();

	private:

		GameContext();
		~GameContext();
		GameContext(GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		void operator=(GameContext&) = delete;
		void operator=(GameContext&&) = delete;

		std::shared_ptr<GameWindow> m_mainWindow;

		RenderSystem* m_renderSystem = nullptr;
		MovementSystem* m_movementSystem = nullptr;
		GameplaySystem* m_gameplaySystem = nullptr;
		PhysicsSystem* m_physicsSystem = nullptr;
	};
}