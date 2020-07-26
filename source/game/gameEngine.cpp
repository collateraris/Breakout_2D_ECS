#include <gameContext.h>
#include <gameEngine.h>
#include <gameWindow.h>

using namespace breakout;

GameEngine::GameEngine()
{
    m_window = GameContext::Get().GetMainWindow();
}

GameEngine::~GameEngine()
{

}

void GameEngine::Init()
{
    m_window->Init();
}

void GameEngine::Start()
{
    while (!m_window->IsOpen())
    {
        m_window->SwapBuffers();
        m_window->PollEvents();
    }

    m_window->Terminate();
}