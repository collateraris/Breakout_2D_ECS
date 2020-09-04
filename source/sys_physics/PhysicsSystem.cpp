#include <PhysicsSystem.h>

#include <SystemManager.h>
#include <CollisionSystem.h>

#include <GameStateManager.h>

using namespace breakout;

PhysicsSystem::PhysicsSystem()
    : BaseSystem()
{
    m_collisionSystem = SystemManager::Get().CreateSystem<CollisionSystem>();
}

PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::Init()
{
    m_collisionSystem->Init();
}

void PhysicsSystem::Update(float dtMilliseconds)
{
    if (GameStateManager::Get().GetCurrentState() != EGameState::GAME)
        return;

    m_collisionSystem->Update(dtMilliseconds);
}