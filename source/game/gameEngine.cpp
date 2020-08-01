#include <gameContext.h>

#include <gameEngine.h>
#include <gameWindow.h>
#include <LogManager.h>
#include <EventsStorage.h>
#include <GameStateManager.h>
#include <AssetsManager.h>
#include <EntityComponentSystem.h>

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

    auto& ecs = GameContext::Get().GetECS();
    ecs.AddComponentByEntityId<BaseComponent>(0);
    ecs.AddComponentByEntityId<BaseComponent>(1);
    ecs.AddComponentByEntityId<BaseComponent>(2);
    ecs.AddComponentByEntityId<BaseComponent>(3);
    ecs.AddComponentByEntityId<BaseComponent>(4);
    auto& components = ecs.GetAllComponentsByType<BaseComponent>();
    auto& component = ComponentManager::Get().GetComponent<BaseComponent>(0);

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