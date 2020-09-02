#include <FontsManager.h>

using namespace breakout;

FontsManager::FontsManager()
	: ResourcesManager<oglml::Font>()
{

};

FontsManager::~FontsManager()
{

};

FontsManager& FontsManager::Get()
{
	static FontsManager fontsManager;
	return fontsManager;
};

bool FontsManager::getFromFile(const std::string& path, oglml::Font& resource)
{
	return resource.loadFromFile(path);
};

