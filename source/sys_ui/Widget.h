#pragma once

namespace breakout
{
	class Widget
	{
	public:

		Widget() = default;
		virtual ~Widget() {};

		virtual void Draw() = 0;
	};
}