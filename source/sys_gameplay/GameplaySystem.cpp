#include <GameplaySystem.h>

#include <SystemManager.h>
#include <PlayerLogicSystem.h>
#include <PlayerBallLogicSystem.h>
#include <DamagableColliderLogicSystem.h>
#include <PowerUpSystem.h>

using namespace breakout;

GameplaySystem::GameplaySystem()
    : BaseSystem()
{

}

GameplaySystem::~GameplaySystem()
{

}

void GameplaySystem::Init()
{
    auto& sm = SystemManager::Get();
    m_playerLogic = sm.CreateSystem<PlayerLogicSystem>();
    m_playerBallLogic = sm.CreateSystem<PlayerBallLogicSystem>();
    m_damageableColliderLogic = sm.CreateSystem<DamagableColliderLogicSystem>();
    m_powerUpLogic = sm.CreateSystem<PowerUpLogicSystem>();

    m_playerLogic->Init();
    m_playerBallLogic->Init();
    m_damageableColliderLogic->Init();
    m_powerUpLogic->Init();
}

void GameplaySystem::Update(float dtMilliseconds)
{
    m_playerLogic->Update(dtMilliseconds);
    m_playerBallLogic->Update(dtMilliseconds);
    m_powerUpLogic->Update(dtMilliseconds);

    m_damageableColliderLogic->Update(dtMilliseconds);
}