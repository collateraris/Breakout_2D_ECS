#pragma once

#include <System.h>

namespace breakout
{
    class PlayerBallLogicSystem : public BaseSystem
    {
        using entityId = int;

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

        void CollitionResolution(entityId, entityId);

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

    private:

        int m_playerEntityId = -1;
        int m_playerBallEntityId = -1;
    };
}