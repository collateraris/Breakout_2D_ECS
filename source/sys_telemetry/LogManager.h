#pragma once

#include <LogListenerInterface.h>
#include <StringHelper.h>

#include <list>
#include <memory>

namespace breakout
{
    class LogManager
    {
    public:

        static LogManager& Get();

		void Init();

		void AddListener(std::shared_ptr<ILogListener> listener);

		void Log(const ILogMessage& message) const;

		void Log(const ELogLevel& level, const ELogChannel& channel, const std::string& str) const;

		template<typename... Targs>
		void Log(const ELogLevel& level, const ELogChannel& channel, const std::string& fstr, const Targs& ... args) const;

		template<typename... Targs>
		void Log(const std::string& fstr, const Targs& ... args) const;

	private:

		LogManager();
		~LogManager();
		LogManager(LogManager&) = delete;
		LogManager(LogManager&&) = delete;
		void operator=(LogManager&) = delete;
		void operator=(LogManager&&) = delete;

		std::list<std::shared_ptr<ILogListener>> m_listenersList;
    };

	template<typename... Targs>
	void LogManager::Log(const ELogLevel& level, const ELogChannel& channel, const std::string& fstr, const Targs& ... args) const
	{
		Log(level, channel, StringHelper::Format(fstr, args...));
	}

	template<typename... Targs>
	void LogManager::Log(const std::string& fstr, const Targs& ... args) const
	{
		Log(ELogLevel::DEBUG, ELogChannel::MAIN, fstr, args...);
	}
}