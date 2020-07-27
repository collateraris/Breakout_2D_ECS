#pragma once

#include <LogMessageInterface.h>

namespace breakout
{
    class ILogListener
    {
    public:
        virtual void Handle(const ILogMessage& message) = 0;
        virtual void Handle(const ELogLevel& level, const ELogChannel& channel, const std::string& text) = 0;
    };
}