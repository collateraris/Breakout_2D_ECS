#include <EntityComponentSystem.h>

#include <SpriteComponent.h>
#include <components/TransformComponent.h>


using namespace breakout;

EntityComponentSystem::EntityComponentSystem()
{
	ComponentManager::Get().CreateComponentPool<SpriteComponent>(5);
	ComponentManager::Get().CreateComponentPool<TransformComponent>(5);

}

EntityComponentSystem::~EntityComponentSystem()
{

}

EntityComponentSystem& EntityComponentSystem::Get()
{
	static EntityComponentSystem ecs;
	return ecs;
}

int EntityComponentSystem::CreateEntityByEntityTypeId(int entityTypeId)
{
	return EntityManager::Get().Create(entityTypeId);
}