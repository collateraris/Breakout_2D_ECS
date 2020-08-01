#pragma once

#include <TextureAssetId.h>
#include <ShaderAssetId.h>

#include <OGLML/Texture2D.h>
#include <OGLML/Shader.h>

#include <string>
#include <unordered_map>

namespace breakout
{
	class AssetManager
	{

	public:

		static AssetManager& Get();

		void LoadAll();
		void UnloadAll();

		void Bind(breakout::ETextureAssetId textureId, const std::string& texturePath);
		bool Get(breakout::ETextureAssetId textureId, oglml::Texture2D& texture);
		bool Load(breakout::ETextureAssetId textureId);
		bool Unload(breakout::ETextureAssetId textureId);

		void Bind(breakout::EShaderAssetId shaderId, const std::string& shaderPath);
		bool Get(breakout::EShaderAssetId shaderId, oglml::Shader& shader);
		bool Load(breakout::EShaderAssetId shaderId);
		bool Unload(breakout::EShaderAssetId shaderId);

	private:

		AssetManager();
		~AssetManager();
		AssetManager(AssetManager&) = delete;
		AssetManager(AssetManager&&) = delete;
		void operator=(AssetManager&) = delete;
		void operator=(AssetManager&&) = delete;

		std::unordered_map<breakout::ETextureAssetId, std::string> m_texturesPaths;
		std::unordered_map<breakout::EShaderAssetId, std::string> m_shadersPaths;
	};
}