#pragma once

#include <System.h>

namespace breakout
{
    class ColliderComponent;

    class PowerUpLogicSystem : public BaseSystem
    {

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::PowerUpLogic;
        }

        PowerUpLogicSystem()
            : BaseSystem() {}


        virtual ~PowerUpLogicSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

        void CollitionResolution(const ColliderComponent&, const ColliderComponent&);

    protected:


    private:

        int m_playerEntityId = -1;
    };
}