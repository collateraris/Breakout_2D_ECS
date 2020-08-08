#include <GameMaps.h>

#include <gameContext.h>
#include <gameWindow.h>
#include <ConfigManager.h>
#include <StringConstants.h>
#include <EntityComponentSystem.h>

#include <ECSBreakout.h>

#include <SpriteComponent.h>
#include <ColliderComponent.h>
#include <components/TransformComponent.h>

#include <OGLML/Sprite.h>

#include <sstream>
#include <fstream>
#include <cassert>

using namespace breakout;

GameMaps::GameMaps()
{

}

GameMaps::~GameMaps()
{

}

GameMaps& GameMaps::Get()
{
	static GameMaps gameMaps;
	return gameMaps;
}

void GameMaps::LoadMap(EGameMapLevels levels)
{
    auto gameLevels = GameContext::Get().GetConfigManager().GetRoot().GetPath(gameMapsStr).GetChildren();
    int id = static_cast<int>(levels);
    auto gameLvl = gameLevels[id];
    std::string path = gameLvl.GetAttribute<std::string>(pathStr);

    std::vector<std::vector<unsigned int>> tileData = {};
    Load(path, tileData);

    assert(tileData.size() > 0);
    GenerateBlocks(tileData);
}

void GameMaps::Load(const std::string& path, std::vector<std::vector<unsigned int>>& tileData)
{
	unsigned int tileCode;
	std::string line;
	std::ifstream fstream(path);

    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
    }
}

void GameMaps::GenerateBlocks(const std::vector<std::vector<unsigned int>>& tileData)
{
    auto window = GameContext::Get().GetMainWindow();

    const unsigned int  lvlWidth = window->GetWidth();
    const unsigned int  lvlHeight = window->GetHeight() / 2;

    const unsigned int tileDataHeight = tileData.size();
    const unsigned int tileDataWidth = tileData[0].size();

    const float unitWidth = static_cast<float>(lvlWidth) / tileDataWidth;
    const float unitHeight = static_cast<float>(lvlHeight) / tileDataHeight;

    const float halfUnitWidth = unitWidth * 0.5f;
    const float halfUnitHeight = unitHeight * 0.5f;

    //init color
    std::vector<std::array<float, 3>> colors =
    {
        { 1.f, 1.f, 1.f }, // 0
        { 0.8f, 0.8f, 0.7f }, // 1
        { 0.2f, 0.6f, 1.0f }, // 2
        { 0.0f, 0.7f, 0.0f }, // 3
        { 0.8f, 0.8f, 0.4f }, // 4
        { 1.0f, 0.5f, 0.0f }, // 5
    };

    auto& ecs = GameContext::Get().GetECS();

    auto CreateSolidBlock = [&]() -> int
    {
        int entityId = ECSBreakout::CreateComponent(EEntityType::SolidBlock);
        return entityId;
    };

    auto CreateBlock = [&]() -> int
    {
        int entityId = ECSBreakout::CreateComponent(EEntityType::Block);
        return entityId;
    };

    auto SetCommonBlockData = [&](int entityId, unsigned int y, unsigned int x, const std::array<float, 3>& color)
    {
        auto& transformComponent = ecs.GetComponentByEntityId<TransformComponent>(entityId);
        std::array<float, 2> pos = { unitWidth * x + halfUnitWidth, unitHeight * y + halfUnitHeight };
        std::array<float, 2> size = { halfUnitWidth, halfUnitHeight };
        transformComponent.SetPosition(pos);
        transformComponent.SetScale(size);

        auto& colliderComponent = ecs.GetComponentByEntityId<ColliderComponent>(entityId);
        colliderComponent.SetSize(size[0], size[1]).SetPosition(pos);

        auto& spriteComponent = ecs.GetComponentByEntityId<SpriteComponent>(entityId);
        spriteComponent.Sprite().SetColor(color);
    };

    for (unsigned int y = 0; y < tileDataHeight; ++y)
    {
        for (unsigned int x = 0; x < tileDataWidth; ++x)
        {
            unsigned int blockType = tileData[y][x];
            
            if (blockType == 1)
            {
                int entityId = CreateSolidBlock();
                SetCommonBlockData(entityId, y, x, colors[blockType]);
            }
            else if (blockType > 1)
            {
                int entityId = CreateBlock();
                SetCommonBlockData(entityId, y, x, colors[blockType]);
            }
        }
    }
}