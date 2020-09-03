#include <CanvasWidgetFabric.h>

#include <TextWidget.h>
#include <CanvasWidget.h>

#include <MemoryManager.h>

#include <cassert>

using namespace breakout;

CanvasWidgetFabric::CanvasWidgetFabric()
{

}

CanvasWidgetFabric::~CanvasWidgetFabric()
{
	auto allocator = MemoryManager::Get().GetGlobalAllocator();

	for (auto& canvasWidget : m_canvasWidgets)
	{
		Deallocate<CanvasWidget>(allocator.get(), canvasWidget.second);
	}
	
	for (auto& textWidget: m_textWidgets )
	{
		Deallocate<TextWidget>(allocator.get(), textWidget);
	}
}

CanvasWidgetFabric& CanvasWidgetFabric::Get()
{
	static CanvasWidgetFabric fabric;
	return fabric;
}

CanvasWidget* CanvasWidgetFabric::GetCanvas(ECanvasType type)
{
	auto& foundCanvasIt = m_canvasWidgets.find(type);
	if (foundCanvasIt != m_canvasWidgets.end())
	{
		auto& canvas = foundCanvasIt->second;
		return canvas;
	}

	return BuildCanvas(type);
}

CanvasWidget* CanvasWidgetFabric::BuildCanvas(ECanvasType type)
{
	switch (type)
	{
	case breakout::ECanvasType::MAIN_MENU:
		return BuildMainMenu();
		break;
	default:
		assert(false);
		return nullptr;
		break;
	}
}

CanvasWidget* CanvasWidgetFabric::BuildMainMenu()
{

}