#pragma once

#include <Component.h>

namespace breakout
{

	class HealthComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::Health;
		};

		void SetHealth(int health)
		{
			m_healthSize = health;
		}

		void LossHealth(int lossSize)
		{
			m_healthSize -= lossSize;
		}

		bool IsDead() const
		{
			return m_healthSize <= 0;
		}

		int GetHealt() const
		{
			return m_healthSize;
		}

	private:

		int m_healthSize = 0;
	};
}