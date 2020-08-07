#include <PhysicsSystem.h>

#include <SystemManager.h>
#include <CollisionSystem.h>

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
    m_collisionSystem->Update(dtMilliseconds);
}