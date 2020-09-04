#pragma once

#include <Widget.h>

#include <vector>

namespace breakout
{
	class CanvasWidget : public Widget
	{
	public:

		CanvasWidget();

		virtual ~CanvasWidget();

		virtual void Draw() override;

		void AddChild(Widget*);

	private:

		std::vector<Widget*> m_children;
	};
}