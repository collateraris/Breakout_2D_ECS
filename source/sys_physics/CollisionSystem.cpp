#include <CollisionSystem.h>

#include <EntityComponentSystem.h>
#include <ColliderComponent.h>

#include <unordered_set>

using namespace breakout;

CollisionSystem::CollisionSystem()
    : BaseSystem()
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::Init()
{

}

void CollisionSystem::Update(float dtMilliseconds)
{
    CollisitionDetection(dtMilliseconds);
}

void CollisionSystem::CollisitionDetection(float dtMilliseconds)
{
    const auto& colliderComponents = EntityComponentSystem::Get().GetAllComponentsByType<ColliderComponent>();

    unsigned int outerCounter = 0;
    unsigned int innerCounter = 0;

    for (const auto& outerIt : colliderComponents)
    {
        outerCounter++;

        innerCounter = 0;
        for (const auto& innerIt : colliderComponents)
        {
            innerCounter++;

            //optimization :triangle
            if (outerCounter <= innerCounter)
                continue;
        }
    }
}