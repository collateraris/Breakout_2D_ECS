#pragma once

#include <Config.h>

#include <memory>

namespace breakout
{
    constexpr char* CONFIG_FILE = "assets/config.xml";

    class ConfigManager
    {
    public:

        static ConfigManager& Get();

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
