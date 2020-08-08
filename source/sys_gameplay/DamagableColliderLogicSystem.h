#pragma once

#include <System.h>

namespace breakout
{
    class DamagableColliderLogicSystem : public BaseSystem
    {
        using entityId = int;

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

        void CollitionResolution(entityId, entityId);
    };
}