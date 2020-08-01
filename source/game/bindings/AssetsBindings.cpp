#include "AssetsBindings.h"

#include <gameContext.h>
#include <ConfigManager.h>
#include <AssetsManager.h>

#include <StringConstants.h>

#include <string>

namespace breakout
{
    void AssetsBindings::BindAll()
    {
        AssetsBindings::BindShaders();
        AssetsBindings::BindTextures();
    }

    void AssetsBindings::BindTextures()
    {
        auto textures = GameContext::Get().GetConfigManager().GetRoot().GetPath(assetsTexturesStr).GetChildren();
        auto& assetManager = GameContext::Get().GetAssetManager();

        for (auto& texture : textures)
        {
            ETextureAssetId id = static_cast<ETextureAssetId>(texture.GetAttribute<int>(idStr));
            std::string path = texture.GetAttribute<std::string>(pathStr);
            assetManager.Bind(id, path);
        }
    }

    void AssetsBindings::BindShaders()
    {
        auto shaders = GameContext::Get().GetConfigManager().GetRoot().GetPath(assetsShadersStr).GetChildren();
        auto& assetManager = GameContext::Get().GetAssetManager();

        for (auto& shader : shaders)
        {
            EShaderAssetId id = static_cast<EShaderAssetId>(shader.GetAttribute<int>(idStr));
            std::string path = shader.GetAttribute<std::string>(pathStr);
            assetManager.Bind(id, path);
        }
    }

}