#include <EntityComponentSystem.h>


using namespace breakout;

EntityComponentSystem::EntityComponentSystem()
{
	ComponentManager::Get().CreateComponentPool<BaseComponent>(20);
}

EntityComponentSystem::~EntityComponentSystem()
{

}

EntityComponentSystem& EntityComponentSystem::Get()
{
	static EntityComponentSystem ecs;
	return ecs;
}