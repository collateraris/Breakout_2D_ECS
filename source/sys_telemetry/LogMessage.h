
#pragma once

#include <LogMessageInterface.h>

namespace breakout
{
    class LogMessage : public ILogMessage
    {
    public:
        LogMessage(const ELogLevel& level, const ELogChannel& channel, const std::string& text) : m_text(text), m_logLevel(level), m_logChannel(channel) {};

        const std::string GetText() const override { return m_text; };
        const ELogLevel GetLevel() const override { return m_logLevel; };
        const ELogChannel GetChannel() const override { return m_logChannel; };

    private:
        std::string m_text;
        ELogLevel m_logLevel;
        ELogChannel m_logChannel;
    };
}