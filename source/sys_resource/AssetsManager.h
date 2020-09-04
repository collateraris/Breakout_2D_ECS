#pragma once

#include <TextureAssetId.h>
#include <ShaderAssetId.h>
#include <SoundAssetId.h>
#include <MusicAssetId.h>
#include <FontsAssetId.h>

#include <string>
#include <unordered_map>

namespace oglml
{
	class Texture2D;
	class Shader;
	class Font;
}

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

		void Bind(breakout::EFontsAssetId fontId, const std::string& fontPath);
		bool Get(breakout::EFontsAssetId fontId, oglml::Font& font);
		bool Load(breakout::EFontsAssetId fontId);
		bool Unload(breakout::EFontsAssetId fontId);

		void Bind(breakout::ESoundAssetId soundId, const std::string& soundPath);
		const std::string& GetPath(breakout::ESoundAssetId soundId);

		void Bind(breakout::EMusicAssetId musicId, const std::string& musicPath);
		const std::string& GetPath(breakout::EMusicAssetId musicId);

	private:

		AssetManager();
		~AssetManager();
		AssetManager(AssetManager&) = delete;
		AssetManager(AssetManager&&) = delete;
		void operator=(AssetManager&) = delete;
		void operator=(AssetManager&&) = delete;

		std::unordered_map<breakout::ETextureAssetId, std::string> m_texturesPaths;
		std::unordered_map<breakout::EShaderAssetId, std::string> m_shadersPaths;
		std::unordered_map<breakout::EFontsAssetId, std::string> m_fontsPaths;
		std::unordered_map<breakout::ESoundAssetId, std::string> m_soundPaths;
		std::unordered_map<breakout::EMusicAssetId, std::string> m_musicPaths;
	};
}