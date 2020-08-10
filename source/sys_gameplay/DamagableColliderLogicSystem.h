#pragma once

#include <System.h>

namespace breakout
{
    class ColliderComponent;

    class DamagableColliderLogicSystem : public BaseSystem
    {
    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::DamagableColliderLogic;
        }

        DamagableColliderLogicSystem()
            : BaseSystem() {}


        virtual ~DamagableColliderLogicSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

        void CollitionResolution(const ColliderComponent&, const ColliderComponent&);
    };
}