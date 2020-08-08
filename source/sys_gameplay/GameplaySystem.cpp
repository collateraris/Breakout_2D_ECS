#include <GameplaySystem.h>

#include <SystemManager.h>
#include <PlayerLogicSystem.h>
#include <PlayerBallLogicSystem.h>
#include <DamagableColliderLogicSystem.h>

using namespace breakout;

GameplaySystem::GameplaySystem()
    : BaseSystem()
{
   m_playerLogic = SystemManager::Get().CreateSystem<PlayerLogicSystem>();
   m_playerBallLogic = SystemManager::Get().CreateSystem<PlayerBallLogicSystem>();
   m_damageableColliderLogic = SystemManager::Get().CreateSystem<DamagableColliderLogicSystem>();
}

GameplaySystem::~GameplaySystem()
{

}

void GameplaySystem::Init()
{
    m_playerLogic->Init();
    m_playerBallLogic->Init();
    m_damageableColliderLogic->Init();
}

void GameplaySystem::Update(float dtMilliseconds)
{
    m_playerLogic->Update(dtMilliseconds);
    m_playerBallLogic->Update(dtMilliseconds);
    m_damageableColliderLogic->Update(dtMilliseconds);
}