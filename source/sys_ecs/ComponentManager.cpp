#include <ComponentManager.h>

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