#pragma once

#include <Component.h>

#include <OGLML/Sprite.h>

namespace breakout
{

	class SpriteComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::Sprite;
		};

		SpriteComponent();
		~SpriteComponent();

		oglml::Sprite& Sprite();

	private:

		oglml::Sprite m_sprite;
	};
}