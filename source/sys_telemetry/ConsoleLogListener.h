#pragma once

#include <AbstractLogListener.h>

namespace breakout
{
    class ConsoleLogListener : public AbstractLogListener
    {
    public:
        ConsoleLogListener(const uint16_t& levelMask, const uint16_t& channelMask);

        virtual ~ConsoleLogListener();

    protected:
        virtual void Write(const std::string& text) override;
    };
}