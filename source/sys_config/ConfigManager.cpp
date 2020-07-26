#include <ConfigManager.h>

#include <ConfigManager.h>

using namespace breakout;

ConfigManager::ConfigManager()
{
	m_config = std::make_unique<Config>(std::string(CONFIG_FILE));
}

ConfigManager::~ConfigManager()
{
}

ConfigManager& ConfigManager::Get()
{
	static ConfigManager configManager;
	return configManager;
}

XPath ConfigManager::GetRoot()
{
	return m_config->GetRoot();
}