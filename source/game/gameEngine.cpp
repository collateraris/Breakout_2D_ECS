#include <gameContext.h>

#include <gameEngine.h>
#include <gameWindow.h>
#include <LogManager.h>
#include <EventsStorage.h>
#include <GameStateManager.h>
#include <AssetsManager.h>
#include <EntityComponentSystem.h>

#include <bindings/AssetsBindings.h>
#include <ShadersManager.h>
#include <TexturesManager.h>

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

    auto& assetManager = GameContext::Get().GetAssetManager();
    assetManager.LoadAll();
    auto& shaderManager = ShadersManager::Get();
    auto& textureManager = TexturesManager::Get();

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