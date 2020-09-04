#include <CanvasWidget.h>

using namespace breakout;

CanvasWidget::CanvasWidget()
{

}

CanvasWidget::~CanvasWidget()
{
	
}

void CanvasWidget::Draw()
{
	for (auto& widget : m_children)
	{
		widget->Draw();
	}
}

void CanvasWidget::AddChild(Widget* widget)
{
	m_children.push_back(widget);
}