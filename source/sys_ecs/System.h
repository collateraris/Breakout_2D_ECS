#pragma once

namespace breakout
{
	enum class EBaseSystemType : int
	{
		None,
		SpriteRender,
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