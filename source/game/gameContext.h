#pragma once

#include <memory>

namespace breakout
{
	class GameWindow;

	class GameContext
	{
	public:

		static GameContext& Get();

		std::shared_ptr<GameWindow>& GetMainWindow();

	private:

		GameContext();
		~GameContext();
		GameContext(GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		void operator=(GameContext&) = delete;
		void operator=(GameContext&&) = delete;

		static GameContext* m_gameContext;

		std::shared_ptr<GameWindow> m_mainWindow;
	};
}