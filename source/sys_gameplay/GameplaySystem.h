#pragma once

#include <System.h>

namespace breakout
{
    class PlayerLogicSystem;

    class GameplaySystem : public BaseSystem
    {

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Gameplay;
        }

        GameplaySystem();

        virtual ~GameplaySystem();

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

    private:

        PlayerLogicSystem* m_playerLogic = nullptr;
    };
}