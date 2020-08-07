#pragma once

#include <Component.h>

#include <array>

namespace breakout
{
	enum class EColliderType
	{
		None,
		Circle,
		Square,
	};

	class ColliderComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::Collider;
		};


		ColliderComponent& SetSize(float width, float height)
		{
			m_width = width;
			m_height = height;
			m_radius = (width > height ? width : height) * 0.5f;
			return *this;
		}

		ColliderComponent& SetCenter(float x, float y)
		{
			m_center = {x, y};
			return *this;
		}

		float GetWidth() const
		{
			return m_width;
		}

		float GetHeight() const
		{
			return m_height;
		}

		float GetRadius() const
		{
			return m_radius;
		}

		const std::array<float, 2>& GetCenter() const
		{
			return m_center;
		}

		ColliderComponent& SetColliderType(EColliderType type)
		{
			m_type = type;
			return *this;
		}

		EColliderType GetColliderType()
		{
			return m_type;
		}

	private:

		float m_width = 0.f;
		float m_height = 0.f;
		float m_radius = 0.f;

		std::array<float, 2> m_center = {0.f , 0.f};

		EColliderType m_type = EColliderType::None;
	};
}