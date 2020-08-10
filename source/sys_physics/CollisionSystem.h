#pragma once

#include <System.h>

#include <list>

namespace breakout
{
    class ColliderComponent;

    class CollisionSystem : public BaseSystem
    {
    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Collision;
        }

        CollisionSystem();

        virtual ~CollisionSystem();

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

        static std::array<float, 2> GetCircle_AABBCollisionDiff(const ColliderComponent& A, const ColliderComponent& B);

    protected:

        void CollisionDetection(float dtMilliseconds);
        void CollisionResolution(const ColliderComponent&, const ColliderComponent&) const;

        bool CheckCollision(const ColliderComponent& A, const ColliderComponent& B) const;

        bool CheckAABB_AABBCollision(const ColliderComponent& A, const ColliderComponent& B) const;

        bool CheckCircle_AABBCollision(const ColliderComponent& A, const ColliderComponent& B) const;
    };
}