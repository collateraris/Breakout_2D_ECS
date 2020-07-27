#pragma once

#include <glew.h>
#include <glfw3.h>

namespace breakout
{
    class GameWindow
    {
    public:
        GameWindow() = default;
        ~GameWindow();

        void Init();

        bool IsOpen() const;

        void PollEvents() const;

        void SwapBuffers();

        void Terminate();

    protected:
        GLFWwindow* m_window = nullptr;
    };
}