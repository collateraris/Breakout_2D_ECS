#pragma once

#include <System.h>
#include <utility>

namespace breakout
{
    class CanvasWidget;

    class GuiSystem : public BaseSystem
    {
        using CurrGameState = int;
    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::GUI;
        }

        GuiSystem();

        virtual ~GuiSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

        void UpdateGUIByGameState();

    private: 

        std::pair<CurrGameState, CanvasWidget*> m_currWidgetByState = {-1, nullptr};

    };
}