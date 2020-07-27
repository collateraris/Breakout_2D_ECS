#pragma once

#include <LogListenerInterface.h>

namespace breakout
{
    class AbstractLogListener : public ILogListener
    {
    public:

        AbstractLogListener(const uint16_t& levelMask, const uint16_t& channelMask);

        virtual ~AbstractLogListener();

        const uint16_t GetLevelMask() const;
        const uint16_t GetChannelMask() const;

        void Handle(const ILogMessage& message) override;
        void Handle(const ELogLevel& level, const ELogChannel& channel, const std::string& text) override;

    protected:

        virtual void Write(const std::string& text) = 0;

    private:

        uint16_t m_levelMask;
        uint16_t m_channelMask;
    };
}