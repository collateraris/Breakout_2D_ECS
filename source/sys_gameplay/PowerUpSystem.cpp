#include <PowerUpSystem.h>

#include <ColliderComponent.h>
#include <CollisionSystem.h>
#include <EventManager.h>

using namespace breakout;

void PowerUpLogicSystem::Init()
{
	EventManager::Get().OnCollitionDetected().BindObject(this, &PowerUpLogicSystem::CollitionResolution);
}

void PowerUpLogicSystem::Update(float dtMilliseconds)
{

}

void PowerUpLogicSystem::CollitionResolution(const ColliderComponent&, const ColliderComponent&)
{

}