#pragma once

#include <System.h>

namespace breakout
{
    class ColliderComponent;
    class TransformComponent;

    class PowerUpLogicSystem : public BaseSystem
    {
        using PowerUpEntityId = int;
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

        bool ShouldSpawn(unsigned int chance);

        void SpawnPowerUps(TransformComponent& initPosition);

        void MoveLogic(PowerUpEntityId, float dtMilliseconds);

    private:

        int m_playerEntityId = -1;
    };
}