#include <GuiSystem.h>

#include <CanvasWidget.h>
#include <CanvasWidgetFabric.h>

#include <GameStateManager.h>

using namespace breakout;

GuiSystem::GuiSystem()
{

}

void GuiSystem::Init()
{

}

void GuiSystem::Update(float dtMilliseconds)
{
	UpdateGUIByGameState();

	auto& canvas = m_currWidgetByState.second;
	if (canvas)
		canvas->Draw();
}

void GuiSystem::UpdateGUIByGameState()
{
	EGameState currGameState = GameStateManager::Get().GetCurrentState();

	if (m_currWidgetByState.first == static_cast<int>(currGameState))
		return;

	auto& canvas = m_currWidgetByState.second;

	switch (currGameState)
	{
	case breakout::EGameState::MAIN_MENU:
		canvas = CanvasWidgetFabric::Get().GetCanvas(ECanvasType::MAIN_MENU);
		break;
	case breakout::EGameState::GAME:
		canvas = CanvasWidgetFabric::Get().GetCanvas(ECanvasType::GAME_ACTIVE);
		break;
	case breakout::EGameState::PAUSE:
		canvas = CanvasWidgetFabric::Get().GetCanvas(ECanvasType::GAME_PAUSE);
		break;
	case breakout::EGameState::GAME_OVER:
		canvas = CanvasWidgetFabric::Get().GetCanvas(ECanvasType::GAME_OVER);
		break;
	case breakout::EGameState::GAME_WIN:
		canvas = CanvasWidgetFabric::Get().GetCanvas(ECanvasType::GAME_WIN);
		break;
	default:
		break;
	}
}