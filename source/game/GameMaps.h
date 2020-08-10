#pragma once

#include <vector>
#include <array>
#include <string>

namespace breakout
{
	enum class EGameMapLevels : int
	{
		None = 0,
		Standard = 1,
		A_few_small_gaps = 2,
		Space_invader = 3,
		Bounce_galore = 4,
		MAX,
	};

	class GameMaps
	{
	public:

		static GameMaps& Get();

		void LoadMap(EGameMapLevels);

	private:

		void Load(const std::string& path, std::vector<std::vector<unsigned int>>& tileData);

		void GenerateBlocks(const std::vector<std::vector<unsigned int>>& tileData);

		GameMaps();
		~GameMaps();
		GameMaps(GameMaps&) = delete;
		GameMaps(GameMaps&&) = delete;
		void operator=(GameMaps&) = delete;
		void operator=(GameMaps&&) = delete;
	};
}