#pragma once

#include <Component.h>

namespace breakout
{
	enum class EPlayerBallState
	{
		IsStuckOnPlayerPaddle,
		Move,
		Sticky,
	};

	class PlayerBallComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::PlayerBall;
		};

		EPlayerBallState state = EPlayerBallState::IsStuckOnPlayerPaddle;
	};
}