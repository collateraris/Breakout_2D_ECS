#pragma once

namespace breakout
{
	enum class EBaseSystemType : int
	{
		None = 0,
		SpriteRender = 1,
		Movement = 2,
		Gameplay = 3,
		PlayerLogic = 4,
		PlayerBallLogic = 5,
		Physics = 6,
		Collision = 7,
		DamagableColliderLogic = 8,
		MAX
	};

	class BaseSystem
	{
	public:
		BaseSystem() {};

		virtual ~BaseSystem() {};

		static EBaseSystemType GetType()
		{
			return EBaseSystemType::None;
		};

		virtual void Init() = 0;

		virtual void Update(float dtMilliseconds) = 0;

	};
}