#include <AbstractLogListener.h>

using namespace breakout;

AbstractLogListener::AbstractLogListener(const uint16_t& levelMask, const uint16_t& channelMask)
	: m_levelMask(levelMask), m_channelMask(channelMask)
{

};

AbstractLogListener::~AbstractLogListener()
{

}

const uint16_t AbstractLogListener::GetLevelMask() const
{ 
	return m_levelMask; 
};

const uint16_t AbstractLogListener::GetChannelMask() const
{ 
	return m_channelMask; 
};

void AbstractLogListener::Handle(const ILogMessage& message)
{
	Handle(message.GetLevel(), message.GetChannel(), message.GetText());
};

void AbstractLogListener::Handle(const ELogLevel& level, const ELogChannel& channel, const std::string& text)
{
	if (GetLevelMask() & static_cast<uint16_t>(level) && GetChannelMask() & static_cast<uint16_t>(channel))
			Write(text);
};

