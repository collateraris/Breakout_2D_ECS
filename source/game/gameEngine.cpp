#include <gameContext.h>

#include <gameEngine.h>
#include <gameWindow.h>
#include <LogManager.h>
#include <EventsStorage.h>
#include <GameStateManager.h>
#include <ConfigManager.h>
#include <InputManager.h>
#include <AssetsManager.h>
#include <EntityComponentSystem.h>
#include <ECSBreakout.h>
#include <GameMaps.h>
#include <GameplaySystem.h>

#include <bindings/AssetsBindings.h>

#include <SpriteRenderSystem.h>
#include <StringConstants.h>

#include <chrono>
#include <thread>

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

    auto fpsOptions = GameContext::Get().GetConfigManager().GetRoot().GetPath(FPSStr).GetChildren();
    m_msPerFrame = 1000 / (fpsOptions[0].GetAttribute<float>(FPSStr));

    LOG("Game Engine Init");
}

void GameEngine::Start()
{
    LOG("Game Engine Start");

    float deltaTime = 0.f;

    float frameStartTime = m_window->GetCurrentTime();

    while (!m_window->IsOpen())
    {
        frameStartTime = m_window->GetCurrentTime();

        deltaTime = m_window->GetDeltaTime();

        GameContext::Get().GetGameplaySystem()->Update(deltaTime);

        Render();

        GameContext::Get().GetEventsStorage().SwapStorages();

        m_window->Update();

        int sleepTime = static_cast<int>(frameStartTime + m_msPerFrame - m_window->GetCurrentTime());
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }

    m_window->Terminate();
}

void GameEngine::Render()
{
    GameContext::Get().GetSpriteRenderSystem()->Render();
}