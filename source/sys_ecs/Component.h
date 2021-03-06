#pragma once

namespace breakout
{
	enum struct EComponentType : int
	{
		None = 0,
		Sprite = 1,
		Transform = 2,
		Movement = 3,
		Player = 4,
		PlayerBall = 5,
		Collider = 6,
		Particles = 7,
		SpriteColor = 8,
		PowerUp = 9,
		Timer = 10,
		Health = 11,
		MAX,
	};

	class BaseComponent
	{
	public:

		int m_componentId = -1;
		int m_entityId = -1;
		int m_componentUniqueId = -1;

		static EComponentType GetType()
		{
			return EComponentType::None;
		};

	};

}