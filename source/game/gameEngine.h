#pragma once

#include <memory>

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

        std::shared_ptr<GameWindow> m_window;
    };
}