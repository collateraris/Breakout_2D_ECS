#pragma once

#include <Component.h>

namespace breakout
{

	class TimerComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::Timer;
		};

		bool bActivated = false;
		float m_Duration = 0.f;
		float m_DecaySpeed = 0.f;
	};
}