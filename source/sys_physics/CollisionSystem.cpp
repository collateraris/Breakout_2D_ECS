#include <CollisionSystem.h>

#include <EntityComponentSystem.h>
#include <ColliderComponent.h>

#include <EventManager.h>
#include <FreeListPoolElement.h>

#include <Vector2.h>

#include <unordered_set>
#include <vector>
#include <algorithm>

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
    CollisionDetection(dtMilliseconds);
}

void CollisionSystem::CollisionDetection(float dtMilliseconds)
{
    const auto& colliderComponents = EntityComponentSystem::Get().GetAllComponentsByType<ColliderComponent>();

    std::vector<FreeListPoolElement<ColliderComponent>*> componentsList(colliderComponents.begin(), colliderComponents.end());
    std::size_t availableComponentNumber = componentsList.size();

    for (std::size_t outerInd = 0; outerInd < availableComponentNumber; ++outerInd)
    {

        if (!componentsList[outerInd]->IsActive())
            continue;

        for (std::size_t innerInd = outerInd + 1; innerInd < availableComponentNumber; ++innerInd)
        {

            if (!componentsList[outerInd]->IsActive())
                break;

            if (!componentsList[innerInd]->IsActive())
                continue;

            const ColliderComponent& A = componentsList[outerInd]->GetContainer();
            const ColliderComponent& B = componentsList[innerInd]->GetContainer();
            if (CheckCollision(A, B))
            {
                CollisionResolution(A, B);
            }
        }
    }


}

void CollisionSystem::CollisionResolution(const ColliderComponent& A, const ColliderComponent& B) const
{
     EventManager::Get().OnCollitionDetected().Broadcast(A, B);
}

bool CollisionSystem::CheckCollision(const ColliderComponent& A, const ColliderComponent& B) const
{
    EColliderType Atype = A.GetColliderType();
    EColliderType Btype = B.GetColliderType();

    if (Atype == EColliderType::Circle && Btype == EColliderType::Square)
        return CheckCircle_AABBCollision(A, B);
    else if (Atype == EColliderType::Square && Btype == EColliderType::Circle)
        return CheckCircle_AABBCollision(B, A);
    else if (Atype == EColliderType::Square && Btype == EColliderType::Square)
        return CheckAABB_AABBCollision(A, B);
    return false;
}


bool CollisionSystem::CheckAABB_AABBCollision(const ColliderComponent& A, const ColliderComponent& B) const
{
    return  A.GetPosition()[0] + A.GetWidth() > B.GetPosition()[0] &&
        B.GetPosition()[0] + B.GetWidth() > A.GetPosition()[0]  &&
        A.GetPosition()[1] + A.GetHeight() > B.GetPosition()[1] &&
        B.GetPosition()[1] + B.GetHeight() > A.GetPosition()[1];
}

std::array<float, 2> CollisionSystem::GetCircle_AABBCollisionDiff(const ColliderComponent& circle, const ColliderComponent& square)
{
    Vector2<float> circleCenter = circle.GetCenter();
    Vector2<float> aabbCenter = square.GetCenter();
    Vector2<float> aabbHalfExtends({ square.GetWidth() * 0.5f, square.GetHeight() * 0.5f });

    Vector2<float> difference = circleCenter - aabbCenter;
    Vector2<float> clamped = Vector2<float>::Clamp(difference, aabbHalfExtends);

    Vector2<float> closest = aabbCenter + clamped;
    difference = closest - circleCenter;
    return difference.data();
}

bool CollisionSystem::CheckCircle_AABBCollision(const ColliderComponent& circle, const ColliderComponent& square) const
{
    Vector2<float> difference = GetCircle_AABBCollisionDiff(circle, square);

    float circleRadius = circle.GetRadius();
    return difference.sqrLength() < circleRadius * circleRadius;
}