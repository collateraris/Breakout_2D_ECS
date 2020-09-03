#pragma once

#include <System.h>

namespace breakout
{
    class GuiSystem : public BaseSystem
    {

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::GUI;
        }

        GuiSystem();

        virtual ~GuiSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;
    };
}