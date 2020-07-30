#include <gameContext.h>

#include <gameEngine.h>
#include <gameWindow.h>
#include <LogManager.h>
#include <EventsStorage.h>
#include <GameStateManager.h>
#include <AssetsManager.h>
#include <FreeListObjectPool.h>
#include <FreeListPoolElement.h>

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
    GameContext::Get().GetLogManager().Init();
    GameContext::Get().GetGameStateManager().Init();
    GameContext::Get().GetEventsStorage().Init();

    FreeListObjectPool<FreeListPoolElement<PoolTestLive>> objpool(100);

    unsigned int poolSize = objpool.GetPoolSize();
    int counter = 0;
    for (unsigned int i = 0; i < poolSize; ++i)
    {
        counter += 10;
        objpool.Activate().SetLive({counter});
    }

    objpool.DeactivateAll();

    LOG("Game Engine Init");
}

void GameEngine::Start()
{
    LOG("Game Engine Start");

    while (!m_window->IsOpen())
    {

        GameContext::Get().GetEventsStorage().SwapStorages();

        m_window->SwapBuffers();
        m_window->PollEvents();
    }

    m_window->Terminate();
}