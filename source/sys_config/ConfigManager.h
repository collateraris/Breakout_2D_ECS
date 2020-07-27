#pragma once

#include <Config.h>

#include <memory>

namespace breakout
{
    enum struct ESystemType
    {
        LogManager = 0,
    };

    constexpr char* CONFIG_FILE = "assets/config.xml";

    class ConfigManager
    {
    public:

        static ConfigManager& Get();

        XPath* Get(ESystemType type) const;

        XPath GetRoot();

    private:

        ConfigManager();
        ~ConfigManager();
        ConfigManager(ConfigManager&) = delete;
        ConfigManager(ConfigManager&&) = delete;
        void operator=(ConfigManager&) = delete;
        void operator=(ConfigManager&&) = delete;


        std::unique_ptr<Config> m_config;
    };
}
