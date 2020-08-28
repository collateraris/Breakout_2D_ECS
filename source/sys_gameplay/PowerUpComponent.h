#pragma once

#include <Component.h>

namespace breakout
{
	enum class EPowerUpType
	{
		None, 
		Speed,
		Sticky,
		PassThrough,
		PadSizeIncrease,
		Confuse,
		Chaos,
	};

	class PowerUpComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::PowerUp;
		};

		EPowerUpType powerUpType = EPowerUpType::None;
	};
}