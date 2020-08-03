#include <ComponentManager.h>

#include <MovementComponent.h>
#include <SpriteComponent.h>
#include <components/TransformComponent.h>

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
	default:
		break;
	}
}