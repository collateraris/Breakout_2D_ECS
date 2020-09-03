#pragma once

#include <array>

namespace breakout
{
	enum class EEntityType : int
	{
		Awersome = 0,
		Background = 1,
		SolidBlock = 2,
		Block = 3,
		PlayerPaddle = 4,
		PlayerBall = 5,
		SpeedPowerUp = 6,
		StickyPowerUp = 7,
		PassThroughPowerUp = 8,
		PadSizeIncreasePowerUp = 9,
		ConfusePowerUp = 10,
		ChaosPowerUp = 11,
		MAX,
    };

	enum class EBreakoutInitGameDataId
	{
		playerPaddleSize = 0,
		playerPaddleVelocity = 1,
		playerBallSize = 2,
		playerBallVelocity = 3,
		powerUpSize = 4,
		powerUpVelocity = 5,
		playerLives = 6,
		MAX = 7
	};

	struct BreakoutInitGameData
	{
		std::array<std::array<float, 2>, 7> data;
	};

	class ECSBreakout
	{
	public:

		static void Init();

		static int CreateComponent(EEntityType);

		static const BreakoutInitGameData& GetInitGameData();

	private:

		static void LoadInitDataFromConfig();

		static void InitComponentsPools();

		static void CreateWorld();

		static void InitGameStateController();

	};
}