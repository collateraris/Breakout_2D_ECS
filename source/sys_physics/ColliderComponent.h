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

	enum class EDamagableType
	{
		None,
		Saved,
		Destroyable,
		Intacted,
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

		ColliderComponent& SetPosition(const std::array<float, 2>& pos)
		{
			m_pos = pos;
			float x_center = pos[0] + m_width * 0.5f;
			float y_center = pos[1] + m_height * 0.5f;
			SetCenter(x_center, y_center);
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

		const std::array<float, 2>& GetPosition() const
		{
			return m_pos;
		}

		ColliderComponent& SetColliderType(EColliderType type)
		{
			m_type = type;
			return *this;
		}

		ColliderComponent& SetDamagableType(EDamagableType type)
		{
			m_damageableType = type;
			return *this;
		}

		EColliderType GetColliderType() const
		{
			return m_type;
		}

		EDamagableType GetDamagableType() const
		{
			return m_damageableType;
		}

	private:

		float m_width = 0.f;
		float m_height = 0.f;
		float m_radius = 0.f;

		std::array<float, 2> m_center = {0.f , 0.f};
		std::array<float, 2> m_pos = { 0.f , 0.f };

		EColliderType m_type = EColliderType::None;
		EDamagableType m_damageableType = EDamagableType::None;
	};
}