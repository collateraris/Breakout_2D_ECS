#pragma once

#include <Component.h>

namespace breakout
{
	class PlayerComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::Player;
		};
	};
}