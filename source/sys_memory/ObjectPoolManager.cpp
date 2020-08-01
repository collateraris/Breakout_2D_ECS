#include <ObjectPoolManager.h>

using namespace breakout;

ObjectPoolManager::ObjectPoolManager()
{

}

ObjectPoolManager::~ObjectPoolManager()
{

}

ObjectPoolManager& ObjectPoolManager::Get()
{
	static ObjectPoolManager objectPoolManager;
	return objectPoolManager;
}