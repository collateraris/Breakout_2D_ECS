#include <AssetsManager.h>

#include <TexturesManager.h>

using namespace breakout;

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	UnloadAll();
}

AssetManager& AssetManager::Get()
{
	static AssetManager assetManager;
	return assetManager;
}

void AssetManager::LoadAll()
{
	TexturesManager& texturesManager = TexturesManager::Get();
	for (auto& path : m_texturesPaths)
		texturesManager.Load(static_cast<int>(path.first), path.second);
}

void AssetManager::UnloadAll()
{
	TexturesManager& texturesManager = TexturesManager::Get();
	for (auto& path : m_texturesPaths)
		texturesManager.Unload(static_cast<int>(path.first));
}

void AssetManager::Bind(breakout::ETextureAssetId textureId, const std::string& texturePath)
{
	m_texturesPaths[textureId] = texturePath;
}

bool AssetManager::Get(breakout::ETextureAssetId textureId, oglml::Texture2D& texture)
{
	int id = static_cast<int>(textureId);
	return TexturesManager::Get().GetResource(id, texture);
}

bool AssetManager::Load(breakout::ETextureAssetId textureId)
{
	int id = static_cast<int>(textureId);
	return TexturesManager::Get().Load(id, m_texturesPaths[textureId]);
}

bool AssetManager::Unload(breakout::ETextureAssetId textureId)
{
	int id = static_cast<int>(textureId);
	return TexturesManager::Get().Unload(id);
}