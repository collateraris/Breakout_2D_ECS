#pragma once

namespace breakout
{
	class GameWindow;

	class GameContext
	{
	public:

		static GameContext& Get();

		GameWindow* GetMainWindow();

	private:

		GameContext();
		~GameContext();
		GameContext(GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		void operator=(GameContext&) = delete;
		void operator=(GameContext&&) = delete;

		static GameContext* m_gameContext;

		GameWindow* m_mainWindow = nullptr;
	};
}