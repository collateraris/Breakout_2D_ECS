#pragma once

#include <string>

namespace breakout
{
    enum struct ELogLevel : uint16_t
    {
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        FATAL = 4
    };

    enum struct ELogChannel : uint16_t
    {
        MAIN = 1
    };

    class ILogMessage
    {
    public:
        virtual const ELogLevel GetLevel() const = 0;
        virtual const ELogChannel GetChannel() const = 0;
        virtual const std::string GetText() const = 0;
    };
}