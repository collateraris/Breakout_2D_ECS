#pragma once

#include <System.h>

namespace breakout
{
    class CollisionSystem;

    class PhysicsSystem : public BaseSystem
    {

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Physics;
        }

        PhysicsSystem();

        virtual ~PhysicsSystem();

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

    private:

        CollisionSystem* m_collisionSystem = nullptr;
    };
}