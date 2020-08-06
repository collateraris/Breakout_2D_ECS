#include <gameContext.h>

#include <gameEngine.h>
#include <gameWindow.h>
#include <LogManager.h>
#include <EventsStorage.h>
#include <GameStateManager.h>
#include <InputManager.h>
#include <AssetsManager.h>
#include <EntityComponentSystem.h>
#include <ECSBreakout.h>
#include <GameMaps.h>
#include <GameplaySystem.h>

#include <bindings/AssetsBindings.h>

#include <SpriteRenderSystem.h>

using namespace breakout;


GameEngine::GameEngine()
{
    m_window = GameContext::Get().GetMainWindow();

    AssetsBindings::BindAll();
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

    GameContext::Get().GetAssetManager().LoadAll();

    m_window->GetKeyButtonDelegate().BindObject(&InputManager::Get(), &InputManager::KeyEnterListener);

    GameContext::Get().GetGameplaySystem()->Init();

    ECSBreakout::Init();
    ECSBreakout::CreateComponent(EEntityType::Background);

    GameMaps::Get().LoadMap(EGameMapLevels::Space_invader);

    ECSBreakout::CreateComponent(EEntityType::PlayerPaddle);


    LOG("Game Engine Init");
}

void GameEngine::Start()
{
    LOG("Game Engine Start");

    while (!m_window->IsOpen())
    {
        m_window->ClearColorBuffer();

        GameContext::Get().GetGameplaySystem()->Update(1.f);

        Render();

        GameContext::Get().GetEventsStorage().SwapStorages();

        m_window->SwapBuffers();
        m_window->PollEvents();
    }

    m_window->Terminate();
}

void GameEngine::Render()
{
    GameContext::Get().GetSpriteRenderSystem()->Render();
}