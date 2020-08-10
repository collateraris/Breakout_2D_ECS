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

    protected:

        void Render();

    private:

        std::shared_ptr<GameWindow> m_window;

        float m_msPerFrame = 16.f;
    };
}