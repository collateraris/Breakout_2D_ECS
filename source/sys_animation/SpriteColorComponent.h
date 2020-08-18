#pragma once

#include <Component.h>

#include <array>

namespace breakout
{

	class SpriteColorComponent : public BaseComponent
	{
	public:

		static EComponentType GetType()
		{
			return EComponentType::SpriteColor;
		};

		SpriteColorComponent();
		~SpriteColorComponent();

		void SetColor(const std::array<float, 3>& color);
		const std::array<float, 3>& GetColor() const;


	private:

		std::array<float, 3> m_color;
	};
}