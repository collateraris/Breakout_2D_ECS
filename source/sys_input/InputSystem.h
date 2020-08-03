#pragma once

#include <System.h>

namespace breakout
{
	class InputSystem : public BaseSystem
	{
    public:
        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Input;
        }

        InputSystem()
            : BaseSystem() {}


        virtual ~InputSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

        void Render();
	};
}