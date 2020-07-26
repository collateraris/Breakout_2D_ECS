#pragma once

#include <memory>

namespace breakout
{
	class GameWindow;
	class ConfigManager;

	class GameContext
	{
	public:

		static GameContext& Get();

		std::shared_ptr<GameWindow>& GetMainWindow();
		ConfigManager& GetConfigManager();

	private:

		GameContext();
		~GameContext();
		GameContext(GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		void operator=(GameContext&) = delete;
		void operator=(GameContext&&) = delete;

		std::shared_ptr<GameWindow> m_mainWindow;
	};
}