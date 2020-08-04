#pragma once

#include <Component.h>

#include <array>

namespace breakout
{
	class MovementComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::Movement;
		};

		MovementComponent();
		~MovementComponent();

		const std::array<float, 2>& GetVelocity() const;

		void SetVelocity(const std::array<float, 2>& velocity);

	private:

		std::array<float, 2> m_velocity = { 1.f, 1.f };
	};
}