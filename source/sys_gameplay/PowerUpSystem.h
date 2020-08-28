#pragma once

#include <System.h>

#include <Vector2.h>

#include <vector>

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

        void ActivatePowerUp(PowerUpEntityId);
        void DeactivatePowerUp(PowerUpEntityId);

        void MoveLogic(PowerUpEntityId, float dtMilliseconds);
        void TimerLogic(PowerUpEntityId, float dtMilliseconds);
        void PowerUpOutsideLogic(PowerUpEntityId);

        void ActivateTimer(PowerUpEntityId, float duration, float decaySpeed);

        void SwitchPostEffect(PowerUpEntityId, int new_effect);
        void TrySetIdlePostEffect(PowerUpEntityId);

        void SetPlayerEntityId();
        void SetPlayerBallEntityId();

    private:

        void AddCandidateToDieList(PowerUpEntityId);
        void DeleteEntityFromDieList();

        int m_playerEntityId = -1;
        int m_playerBallEntityId = -1;

        std::vector<int> m_dieListCandidate = {};
        int m_currentDieListPos = 0;

        int m_currPostEffectEntityId = 0;
    };
}