#include <ConsoleLogListener.h>

#include <iostream>

using namespace breakout;

ConsoleLogListener::ConsoleLogListener(const uint16_t& levelMask, const uint16_t& channelMask)
	: AbstractLogListener(levelMask, channelMask)
{

}

ConsoleLogListener::~ConsoleLogListener()
{

}

void ConsoleLogListener::Write(const std::string& text)
{
	std::cout << text << std::endl;
}