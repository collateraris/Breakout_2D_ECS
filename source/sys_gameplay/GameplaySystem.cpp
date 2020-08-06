#include <GameplaySystem.h>

#include <SystemManager.h>
#include <PlayerLogicSystem.h>

using namespace breakout;

GameplaySystem::GameplaySystem()
    : BaseSystem()
{

   m_playerLogic = SystemManager::Get().CreateSystem<PlayerLogicSystem>();
}

GameplaySystem::~GameplaySystem()
{

}

void GameplaySystem::Init()
{
    m_playerLogic->Init();
}

void GameplaySystem::Update(float dtMilliseconds)
{
    m_playerLogic->Update(dtMilliseconds);
}