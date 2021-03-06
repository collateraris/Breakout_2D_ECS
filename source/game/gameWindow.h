#pragma once

#include <glew.h>
#include <glfw3.h>

#include <Delegate.h>
#include <OGLML/InputCode.h>

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

        void Update();

        void Terminate();

        void ClearColorBuffer();

        int GetWidth();

        int GetHeight();

        float GetDeltaTime();

        void CalculateDeltaTime();

        float GetCurrentTime();

        MulticastDelegate<oglml::EKeyButtonCode, oglml::EActionCode, oglml::EKeyModeCode>& GetKeyButtonDelegate();

    protected:

        GLFWwindow* m_window = nullptr;

        int m_width = 0;
        int m_height = 0;

        float m_deltaTime = 0.f;
    };
}