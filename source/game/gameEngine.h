#pragma once

namespace breakout
{
    class GameWindow;

    class GameEngine
    {
    public:
        GameEngine();
        ~GameEngine();

        void Init();
        void Start();

    private:
        GameWindow* m_window = nullptr;
    };
}