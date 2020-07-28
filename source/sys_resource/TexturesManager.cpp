#include <TexturesManager.h>

using namespace breakout;

TexturesManager::TexturesManager()
	: ResourcesManager<oglml::Texture2D>()
{

};

TexturesManager::~TexturesManager()
{

};

TexturesManager& TexturesManager::Get()
{
	static TexturesManager texturesManager;
	return texturesManager;
};

bool TexturesManager::getFromFile(const std::string& path, oglml::Texture2D& resource)
{
	return true;
};
