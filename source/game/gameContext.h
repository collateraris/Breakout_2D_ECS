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

	class SpriteRenderSystem;
	class MovementSystem;

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

		SpriteRenderSystem* GetSpriteRenderSystem();
		MovementSystem* GetMovementSystem();

	private:

		GameContext();
		~GameContext();
		GameContext(GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		void operator=(GameContext&) = delete;
		void operator=(GameContext&&) = delete;

		std::shared_ptr<GameWindow> m_mainWindow;

		SpriteRenderSystem* m_spriteRenderSystem = nullptr;
		MovementSystem* m_movementSystem = nullptr;
	};
}