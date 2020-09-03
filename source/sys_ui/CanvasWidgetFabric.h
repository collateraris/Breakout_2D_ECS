#pragma once

#include <vector>
#include <unordered_map>

namespace breakout
{
	enum class ECanvasType
	{
		MAIN_MENU,
	};

	class CanvasWidget;
	class TextWidget;

	class CanvasWidgetFabric
	{

	public:

		static CanvasWidgetFabric& Get();

		CanvasWidget* GetCanvas(ECanvasType);

	private:

		CanvasWidget* BuildCanvas(ECanvasType);

		CanvasWidget* BuildMainMenu();

		CanvasWidgetFabric();
		~CanvasWidgetFabric();
		CanvasWidgetFabric(CanvasWidgetFabric&) = delete;
		CanvasWidgetFabric(CanvasWidgetFabric&&) = delete;
		void operator=(CanvasWidgetFabric&) = delete;
		void operator=(CanvasWidgetFabric&&) = delete;

		std::unordered_map<ECanvasType, CanvasWidget*> m_canvasWidgets;
		std::vector<TextWidget*> m_textWidgets = {};
	};
}