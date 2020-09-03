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
#include <RenderSystem.h>
#include <GameplaySystem.h>
#include <PhysicsSystem.h>

#include <OGLML/Font.h>
#include <OGLML/Text.h>
#include <OGLML/Shader.h>

#include <bindings/AssetsBindings.h>

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

    GameContext::Get().GetPhysicsSystem()->Init();
    GameContext::Get().GetGameplaySystem()->Init();
    GameContext::Get().GetRenderSystem()->Init();

    ECSBreakout::Init();

    auto fpsOptions = GameContext::Get().GetConfigManager().GetRoot().GetPath(FPSStr).GetChildren();
    m_msPerFrame = 1000 / (fpsOptions[0].GetAttribute<float>(FPSStr));
         
    LOG("Game Engine Init");
}

void GameEngine::Start()
{
    LOG("Game Engine Start");

    float deltaTime = 0.f;

    float frameStartTime = m_window->GetCurrentTime();

    oglml::Font font;
    AssetManager::Get().Get(EFontsAssetId::ocraext, font);

    oglml::Shader shader;
    AssetManager::Get().Get(EShaderAssetId::Text_2D, shader);

    oglml::TextInfo textInfo;
    textInfo.shaderId = shader.GetProgramID();
    textInfo.width = 800;
    textInfo.height = 600;

    oglml::Text text(textInfo);
    text.SetFont(font);
    text.SetCharacterSize(48);
    text.SetOffset(25.0f, 25.0f, 1.0f);
    text.SetFillColor({ 0.5, 0.8f, 0.2f });
    text.SetString("Breakout is super GAME");

    while (!m_window->IsOpen())
    {
        frameStartTime = m_window->GetCurrentTime();

        deltaTime = m_window->GetDeltaTime();

        GameContext::Get().GetPhysicsSystem()->Update(deltaTime);
        GameContext::Get().GetGameplaySystem()->Update(deltaTime);
        GameContext::Get().GetRenderSystem()->Update(deltaTime);
        text.Draw();

        GameContext::Get().GetEventsStorage().SwapStorages();

        m_window->Update();

        int sleepTime = static_cast<int>(frameStartTime + m_msPerFrame - m_window->GetCurrentTime());
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }

    m_window->Terminate();
}
