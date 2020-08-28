#pragma once

#include <Component.h>

#include <array>

namespace breakout
{
	class TransformComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::Transform;
		};

		void operator=(const TransformComponent&);

		const std::array<float, 2>& GetPosition() const;
		TransformComponent& SetPosition(const std::array<float, 2>& newPosition);

		float GetRotation() const;
		TransformComponent& SetRotation(float newRotation);

		const std::array<float, 2>& GetScale() const;
		TransformComponent& SetScale(const std::array<float, 2>& newScale);

	private:

		std::array<float, 2> m_position = { 0.0f, 0.0f };
		float m_rotation = 0.f;
		std::array<float, 2> m_scale = { 1.0f, 1.0f };
	};
}