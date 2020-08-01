#include <EntityManager.h>

using namespace breakout;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

EntityManager& EntityManager::Get()
{
	static EntityManager entityManager;
	return entityManager;
}