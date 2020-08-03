#pragma once

#include <Component.h>

#include <array>
#include <functional>

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

		void SetUpdateFunction(const std::function<void(int, int, float)>& update);

		void Update(float dtMilliseconds);

	private:

		std::array<float, 2> m_velocity = { 1.f, 1.f };

		std::function<void(int, int, float)> m_updateFunction;
	};
}