#include <AssetsManager.h>

#include <TexturesManager.h>
#include <ShadersManager.h>

#include <cassert>

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

	ShadersManager& shadersManager =ShadersManager::Get();
	for (auto& path : m_shadersPaths)
		shadersManager.Load(static_cast<int>(path.first), path.second);

}

void AssetManager::UnloadAll()
{
	TexturesManager& texturesManager = TexturesManager::Get();
	for (auto& path : m_texturesPaths)
		texturesManager.Unload(static_cast<int>(path.first));

	ShadersManager& shadersManager = ShadersManager::Get();
	for (auto& path : m_shadersPaths)
		shadersManager.Unload(static_cast<int>(path.first));

}

//----------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------

void AssetManager::Bind(breakout::EShaderAssetId shaderId, const std::string& shaderPath)
{
	m_shadersPaths[shaderId] = shaderPath;
}

bool AssetManager::Get(breakout::EShaderAssetId shaderId, oglml::Shader& shader)
{
	int id = static_cast<int>(shaderId);
	return ShadersManager::Get().GetResource(id, shader);
}

bool AssetManager::Load(breakout::EShaderAssetId shaderId)
{
	int id = static_cast<int>(shaderId);
	return ShadersManager::Get().Load(id, m_shadersPaths[shaderId]);
}

bool AssetManager::Unload(breakout::EShaderAssetId shaderId)
{
	int id = static_cast<int>(shaderId);
	return ShadersManager::Get().Unload(id);
}

void AssetManager::Bind(breakout::ESoundAssetId soundId, const std::string& soundPath)
{
	m_soundPaths[soundId] = soundPath;
}

const std::string& AssetManager::GetPath(breakout::ESoundAssetId soundId)
{
	assert(m_soundPaths.find(soundId) != m_soundPaths.end());
	return m_soundPaths[soundId];
}


void AssetManager::Bind(breakout::EMusicAssetId musicId, const std::string& musicPath)
{
	m_musicPaths[musicId] = musicPath;
}

const std::string& AssetManager::GetPath(breakout::EMusicAssetId musicId)
{
	assert(m_musicPaths.find(musicId) != m_musicPaths.end());
	return m_musicPaths[musicId];
}