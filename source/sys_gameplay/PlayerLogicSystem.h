#pragma once

#include <System.h>

namespace breakout
{
    class PlayerLogicSystem : public BaseSystem
    {

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::PlayerLogic;
        }

        PlayerLogicSystem()
            : BaseSystem() {}


        virtual ~PlayerLogicSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

    protected:

        void MoveLeftAction(float dtMilliseconds);
        void MoveRightAction(float dtMilliseconds);
        void SetPosition(bool axis /* false - x, true - y*/, short int velocitySign /* <0 - negative, >= - positive*/, float dtMilliseconds);

        void SetPlayerEntityId();

        void Restart();

        void SetInitPos();

    private:

        int m_playerEntityId = -1;
    };
}