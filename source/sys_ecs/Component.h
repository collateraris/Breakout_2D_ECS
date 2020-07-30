#pragma once

namespace breakout
{
	enum struct EComponentType : unsigned int
	{
		None,
		Sprite,
		MAX,
	};

	class BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::None;
		};

	protected:

		unsigned int m_id = 0;

	};

	class TestComponent : BaseComponent
	{
	public:

		TestComponent() {};


		static EComponentType GetType()
		{
			return EComponentType::Sprite;
		};

		int a = 0;
	};
}