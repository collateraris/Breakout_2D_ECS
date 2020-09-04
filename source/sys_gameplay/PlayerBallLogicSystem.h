#pragma once

#include <System.h>

#include <array>

namespace breakout
{
    class ColliderComponent;

    class PlayerBallLogicSystem : public BaseSystem
    {
    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::PlayerBallLogic;
        }

        PlayerBallLogicSystem()
            : BaseSystem() {}


        virtual ~PlayerBallLogicSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

        void CollitionResolution(const ColliderComponent&, const ColliderComponent&);

    protected:

        void IsStuckOnPlayerPaddleLogic(float dtMilliseconds);
        void MoveLogic(float dtMilliseconds);

        void PlayerSpaceClickAction(float dtMilliseconds);

        void PlayerMoveLeftAction(float dtMilliseconds);
        void PlayerMoveRightAction(float dtMilliseconds);
        void SetPosition(bool axis /* false - x, true - y*/, short int velocitySign /* <0 - negative, >= - positive*/, float dtMilliseconds);

        void SetPlayerEntityId();
        void SetPlayerBallEntityId();
        void SetInitPosition();

        void BallParticlesShow();

        void BlockCollition(const ColliderComponent&, const ColliderComponent&) const;
        void PaddlePlayerCollition(const ColliderComponent&, const ColliderComponent&) const;

        void LossHealth();

    private:

        int m_playerEntityId = -1;
        int m_playerBallEntityId = -1;
    };
}