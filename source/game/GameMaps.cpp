#include <GameMaps.h>

#include <gameContext.h>
#include <gameWindow.h>
#include <ConfigManager.h>
#include <StringConstants.h>
#include <EntityComponentSystem.h>

#include <ECSBreakout.h>
#include <EventManager.h>

#include <SpriteComponent.h>
#include <SpriteColorComponent.h>
#include <ColliderComponent.h>
#include <components/TransformComponent.h>

#include <OGLML/Sprite.h>

#include <sstream>
#include <fstream>
#include <cassert>
#include <algorithm>

using namespace breakout;

GameMaps::GameMaps()
{

}

GameMaps::~GameMaps()
{
    DestroyCurrLevel();
}

GameMaps& GameMaps::Get()
{
	static GameMaps gameMaps;
	return gameMaps;
}

void GameMaps::LoadMap(EGameMapLevels levels)
{
    m_currLevel = levels;

    auto gameLevels = GameContext::Get().GetConfigManager().GetRoot().GetPath(gameMapsStr).GetChildren();
    int id = static_cast<int>(levels);
    auto gameLvl = gameLevels[id];
    std::string path = gameLvl.GetAttribute<std::string>(pathStr);

    std::vector<std::vector<unsigned int>> tileData = {};
    Load(path, tileData);

    assert(tileData.size() > 0);
    m_blocks = 0;
    GenerateBlocks(tileData);

    EventManager::Get().OnNewLevelLoaded().Broadcast();
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

    const float errorPercent = 0.05f;
    const float errorWidth = unitWidth * errorPercent;
    const float errorHeight = unitHeight * errorPercent;

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
        m_usedEntityId.push_back(entityId);
        return entityId;
    };

    auto CreateBlock = [&]() -> int
    {
        int entityId = ECSBreakout::CreateComponent(EEntityType::Block);
        m_usedEntityId.push_back(entityId);
        m_blocks++;
        return entityId;
    };

    auto SetCommonBlockData = [&](int entityId, unsigned int y, unsigned int x, const std::array<float, 3>& color)
    {
        auto& transformComponent = ecs.GetComponentByEntityId<TransformComponent>(entityId);
        std::array<float, 2> pos = { unitWidth * x , unitHeight * y};
        std::array<float, 2> size = { unitWidth, unitHeight};
        transformComponent.SetPosition(pos);
        transformComponent.SetScale(size);

        auto& colliderComponent = ecs.GetComponentByEntityId<ColliderComponent>(entityId);
        colliderComponent.SetSize(size[0] - errorWidth, size[1] - errorHeight).SetPosition(pos);

        if (ecs.IsContainComponentByEntityId<SpriteColorComponent>(entityId))
        {
            auto& spriteColorComponent = ecs.GetComponentByEntityId<SpriteColorComponent>(entityId);
            spriteColorComponent.SetColor(color);
        }
        else
        {
            auto& spriteComponent = ecs.GetComponentByEntityId<SpriteComponent>(entityId);
            spriteComponent.Sprite().SetColor(color);
        }
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

void GameMaps::NextLevel()
{
    DestroyCurrLevel();

    int currLevelId = static_cast<int>(m_currLevel);
    int firstLevelId = static_cast<int>(EGameMapLevels::Standard);
    int lastLevelId = static_cast<int>(EGameMapLevels::MAX);
    int nextLevel = (currLevelId + 1) % lastLevelId;
    nextLevel = std::clamp(nextLevel, firstLevelId, lastLevelId);

    EGameMapLevels newLevel = static_cast<EGameMapLevels>(nextLevel);
    LoadMap(newLevel);
}

void GameMaps::PrevLevel()
{
    DestroyCurrLevel();

    int currLevelId = static_cast<int>(m_currLevel);
    int firstLevelId = static_cast<int>(EGameMapLevels::Standard);
    int lastLevelId = static_cast<int>(EGameMapLevels::MAX);
    int prevLevel = currLevelId - 1;
    prevLevel = prevLevel < firstLevelId ? lastLevelId - 1 : prevLevel;

    EGameMapLevels newLevel = static_cast<EGameMapLevels>(prevLevel);
    LoadMap(newLevel);
}

void GameMaps::DestroyCurrLevel()
{
    auto& ecs = EntityComponentSystem::Get();
    for (int entityId : m_usedEntityId)
    {
        if(ecs.IsExistEntityId(entityId))
            ecs.EntityDestroy(entityId);
    }

    m_usedEntityId.clear();
}

int GameMaps::GetBlockNum() const
{
   return m_blocks;
}