#include <TexturesManager.h>

#include <ConfigManager.h>
#include <StringConstants.h>

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
	return resource.loadFromFile(path);
};

bool TexturesManager::Load(int resourceId, const std::string& path)
{
	auto textures = ConfigManager::Get().GetRoot().GetPath(assetsTexturesStr).GetChildren();
	bool usingAplha = textures[resourceId].GetAttribute<bool>(alphaStr);

	oglml::Texture2D resource;
	if (!resource.loadFromFile(path, usingAplha))
		return false;

	ResourcesManager<oglml::Texture2D>::SetResource(resourceId, resource);
	return true;
}
