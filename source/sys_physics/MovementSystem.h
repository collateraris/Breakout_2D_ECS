#pragma once

#include <System.h>

namespace breakout
{
    class MovementSystem : public BaseSystem
    {
    public:
        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Movement;
        }

        MovementSystem()
            : BaseSystem() {}


        virtual ~MovementSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

        void Render();
    };
}