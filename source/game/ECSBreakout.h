#pragma once

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

	class ECSBreakout
	{
	public:

		static void Init();

		static int CreateComponent(EEntityType);

	private:

		static void InitComponentsPools();

		static void CreateWorld();
	};
}