#pragma once

#include <System.h>

#include <list>

namespace breakout
{
    class ColliderComponent;

    class CollisionSystem : public BaseSystem
    {
        using entityId = int;
    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Collision;
        }

        CollisionSystem();

        virtual ~CollisionSystem();

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

    protected:

        void CollisionDetection(float dtMilliseconds);
        void CollisionResolution(entityId, entityId);

        bool CheckCollision(const ColliderComponent& A, const ColliderComponent& B) const;

        bool CheckAABB_AABBCollision(const ColliderComponent& A, const ColliderComponent& B) const;

        bool CheckCircle_AABBCollision(const ColliderComponent& A, const ColliderComponent& B) const;
    };
}