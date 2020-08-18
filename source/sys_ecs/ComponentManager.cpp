#include <ComponentManager.h>

#include <MovementComponent.h>
#include <SpriteComponent.h>
#include <SpriteColorComponent.h>
#include <components/TransformComponent.h>
#include <ColliderComponent.h>
#include <PlayerBallComponent.h>
#include <PlayerComponent.h>
#include <ParticlesComponent.h>


using namespace breakout;

ComponentManager::ComponentManager()
{

}

ComponentManager::~ComponentManager()
{

}

ComponentManager& ComponentManager::Get()
{
	static ComponentManager componentManager;
	return componentManager;
}

void ComponentManager::Delete(EComponentType type, int componentId)
{
	switch (type)
	{
	case breakout::EComponentType::Sprite:
		Delete<SpriteComponent>(componentId);
		break;
	case breakout::EComponentType::Transform:
		Delete<TransformComponent>(componentId);
		break;
	case breakout::EComponentType::Movement:
		Delete<MovementComponent>(componentId);
		break;
	case breakout::EComponentType::Player:
		Delete<PlayerComponent>(componentId);
		break;
	case breakout::EComponentType::PlayerBall:
		Delete<PlayerBallComponent>(componentId);
		break;
	case breakout::EComponentType::Collider:
		Delete<ColliderComponent>(componentId);
		break;
	case breakout::EComponentType::Particles:
		Delete<ParticlesComponent>(componentId);
		break;
	case breakout::EComponentType::SpriteColor:
		Delete<SpriteColorComponent>(componentId);
		break;
	default:
		break;
	}
}