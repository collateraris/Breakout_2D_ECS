#pragma once

#include <glew.h>
#include <glfw3.h>

#include <Delegate.h>

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

        void ClearColorBuffer();

        int GetWidth();

        int GetHeight();

        Delegate& GetKeyButtonDelegate();

        Delegate& GetMouseClickDelegate();

    protected:

        GLFWwindow* m_window = nullptr;

        int m_width = 0;
        int m_height = 0;
    };
}