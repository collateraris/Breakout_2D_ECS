#include <CanvasWidgetFabric.h>

#include <TextWidget.h>
#include <CanvasWidget.h>

#include <MemoryManager.h>
#include <AssetsManager.h>
#include <gameContext.h>
#include <ECSBreakout.h>
#include <EntityComponentSystem.h>
#include <HealthComponent.h>

#include <StringConstants.h>

#include <OGLML/Font.h>
#include <OGLML/Text.h>

#include <cassert>
#include <functional>

using namespace breakout;

CanvasWidgetFabric::CanvasWidgetFabric()
{

}

CanvasWidgetFabric::~CanvasWidgetFabric()
{
	auto allocator = MemoryManager::Get().GetGlobalAllocator();

	for (auto& canvasWidget : m_canvasWidgets)
	{
		deallocate<CanvasWidget>(allocator.get(), canvasWidget.second);
	}
	
	for (auto& textWidget: m_textWidgets )
	{
		deallocate<TextWidget>(allocator.get(), textWidget);
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
	case breakout::ECanvasType::GAME_ACTIVE:
		return BuildGameActive();
	case breakout::ECanvasType::GAME_PAUSE:
		return BuildGamePause();
	case breakout::ECanvasType::GAME_OVER:
		return BuildGameOver();
	case breakout::ECanvasType::GAME_WIN:
		return BuildGameWin();
	default:
		assert(false);
		return nullptr;
		break;
	}
}

CanvasWidget* CanvasWidgetFabric::BuildMainMenu()
{
	CanvasWidget* mainMenu = AllocateCanvasWidget(ECanvasType::MAIN_MENU);

	auto& assetManager = AssetManager::Get();

	static oglml::Font font;
	assetManager.Get(EFontsAssetId::ocraext, font);

	int w, h;
	GameContext::Get().GetMainWindowSize(w, h);

	{
		TextWidget* textWidget = AllocateTextWidget();
		mainMenu->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(24);
		text.SetOffset(5.0f, 5.0f, 1.0f);
		int lives = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::playerLives)][0];
		text.SetString(livesTextStr + std::to_string(lives));
	}

	{
		TextWidget* textWidget = AllocateTextWidget();
		mainMenu->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(24);
		text.SetOffset(185.0f, static_cast<float>(h) / 2.0f, 1.0f);
		text.SetString(pressEnterToStartTextStr);
	}

	{
		TextWidget* textWidget = AllocateTextWidget();
		mainMenu->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(24);
		text.SetOffset(245.0f, static_cast<float>(h) / 2.0f + 20.0f, 0.75f);
		text.SetString(pressXXtoSelectLevelTextStr);
	}

	return mainMenu;
}

CanvasWidget* CanvasWidgetFabric::BuildGameActive()
{
	CanvasWidget* gameActive = AllocateCanvasWidget(ECanvasType::GAME_ACTIVE);

	auto& assetManager = AssetManager::Get();

	static oglml::Font font;
	assetManager.Get(EFontsAssetId::ocraext, font);

	{
		TextWidget* textWidget = AllocateTextWidget();
		gameActive->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(24);
		text.SetOffset(5.0f, 5.0f, 1.0f);
		int playerId = ECSBreakout::GetInitGameData().playerId;
		static auto playerHealth = &EntityComponentSystem::Get().GetComponentByEntityId<HealthComponent>(playerId);
		text.SetString(livesTextStr + std::to_string(playerHealth->GetHealt()));

		std::function<void(oglml::Text*)> updateFunc = [&](oglml::Text* text)
		{
			static int prevPlayerHealth = -1;
			int currPlayerHealth = playerHealth->GetHealt();
			if (currPlayerHealth == prevPlayerHealth)
				return;
			prevPlayerHealth = currPlayerHealth;

			text->SetString(livesTextStr + std::to_string(currPlayerHealth));
		};

		textWidget->SetUpdateFunc(updateFunc);
	}

	return gameActive;
}

CanvasWidget* CanvasWidgetFabric::BuildGamePause()
{
	CanvasWidget* gamePause = AllocateCanvasWidget(ECanvasType::GAME_PAUSE);

	auto& assetManager = AssetManager::Get();

	static oglml::Font font;
	assetManager.Get(EFontsAssetId::ocraext, font);

	int w, h;
	GameContext::Get().GetMainWindowSize(w, h);

	{
		TextWidget* textWidget = AllocateTextWidget();
		gamePause->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(24);
		text.SetOffset(5.0f, 5.0f, 1.0f);
		int playerId = ECSBreakout::GetInitGameData().playerId;
		static auto playerHealth = &EntityComponentSystem::Get().GetComponentByEntityId<HealthComponent>(playerId);
		text.SetString(livesTextStr + std::to_string(playerHealth->GetHealt()));
	}

	{
		TextWidget* textWidget = AllocateTextWidget();
		gamePause->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(24);
		text.SetOffset(290.0f, static_cast<float>(h) / 2.0f, 1.25f);
		text.SetString(gamePauseTextStr);
	}

	{
		TextWidget* textWidget = AllocateTextWidget();
		gamePause->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(24);
		text.SetOffset(static_cast<float>(w) / 2.0f - 100.f, static_cast<float>(h) / 2.0f + 20.0f, 0.75f);
		text.SetString(pressEntertoRetryTextStr);
	}

	return gamePause;
}

CanvasWidget* CanvasWidgetFabric::BuildGameOver()
{
	CanvasWidget* gameOver = AllocateCanvasWidget(ECanvasType::GAME_OVER);

	auto& assetManager = AssetManager::Get();

	static oglml::Font font;
	assetManager.Get(EFontsAssetId::ocraext, font);

	int w, h;
	GameContext::Get().GetMainWindowSize(w, h);

	{
		TextWidget* textWidget = AllocateTextWidget();
		gameOver->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(45);
		text.SetOffset(290.0f, static_cast<float>(h) / 2.0f, 1.f);
		text.SetString(gameOverTextStr);
	}

	return gameOver;
}

CanvasWidget* CanvasWidgetFabric::BuildGameWin()
{
	CanvasWidget* gameWin = AllocateCanvasWidget(ECanvasType::GAME_OVER);

	auto& assetManager = AssetManager::Get();

	static oglml::Font font;
	assetManager.Get(EFontsAssetId::ocraext, font);

	int w, h;
	GameContext::Get().GetMainWindowSize(w, h);

	{
		TextWidget* textWidget = AllocateTextWidget();
		gameWin->AddChild(textWidget);
		auto& text = textWidget->GetText();
		text.SetFont(font);
		text.SetCharacterSize(45);
		text.SetOffset(290.0f, static_cast<float>(h) / 2.0f, 1.f);
		text.SetString(youWONTextStr);
	}

	return gameWin;
}

CanvasWidget* CanvasWidgetFabric::AllocateCanvasWidget(ECanvasType type)
{
	auto allocator = MemoryManager::Get().GetGlobalAllocator();
	CanvasWidget* canvas = allocate<CanvasWidget>(allocator.get());
	m_canvasWidgets.insert({type, canvas});

	return canvas;
}

TextWidget* CanvasWidgetFabric::AllocateTextWidget()
{
	auto allocator = MemoryManager::Get().GetGlobalAllocator();
	TextWidget* text = allocate<TextWidget>(allocator.get());
	m_textWidgets.push_back(text);

	return text;
}