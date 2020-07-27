#include <LogManager.h>

#include <ConsoleLogListener.h>

#include <cassert>
#include <gameContext.h>
#include <ConfigManager.h>

using namespace breakout;

LogManager::LogManager()
{

}

LogManager::~LogManager()
{

}

LogManager& LogManager::Get()
{
	static LogManager logManager;
	return logManager;
}

void LogManager::Init()
{
    XPath* config = GameContext::Get().GetConfigManager().Get(ESystemType::LogManager);
    assert(config != nullptr);
    if (config == nullptr)
        return;

    auto consoleLogListener = std::make_shared<ConsoleLogListener>(UINT16_MAX, UINT16_MAX);
    AddListener(consoleLogListener);
}

void LogManager::AddListener(std::shared_ptr<ILogListener> listener)
{
    m_listenersList.emplace_back(listener);
}

void LogManager::Log(const ILogMessage& message) const
{
    for (const auto& listener : m_listenersList)
        listener->Handle(message);
}

void LogManager::Log(const ELogLevel& level, const ELogChannel& channel, const std::string& str) const
{
    for (const auto& listener : m_listenersList)
        listener->Handle(level, channel, str);
}