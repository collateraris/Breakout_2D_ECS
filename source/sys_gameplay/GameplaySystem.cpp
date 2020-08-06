#include <GameplaySystem.h>

#include <SystemManager.h>
#include <PlayerLogicSystem.h>
#include <PlayerBallLogicSystem.h>

using namespace breakout;

GameplaySystem::GameplaySystem()
    : BaseSystem()
{
   m_playerLogic = SystemManager::Get().CreateSystem<PlayerLogicSystem>();
   m_playerBallLogic = SystemManager::Get().CreateSystem<PlayerBallLogicSystem>();
}

GameplaySystem::~GameplaySystem()
{

}

void GameplaySystem::Init()
{
    m_playerLogic->Init();
    m_playerBallLogic->Init();
}

void GameplaySystem::Update(float dtMilliseconds)
{
    m_playerLogic->Update(dtMilliseconds);
    m_playerBallLogic->Update(dtMilliseconds);
}