#include <TextWidget.h>

#include <MemoryManager.h>
#include <AssetsManager.h>
#include <gameContext.h>

#include <OGLML/Text.h>
#include <OGLML/Shader.h>


using namespace breakout;

TextWidget::TextWidget()
{
	auto& assetManager = AssetManager::Get();

	oglml::Shader shader;
	assetManager.Get(EShaderAssetId::Text_2D, shader);

	int w, h;
	GameContext::Get().GetMainWindowSize(w, h);

	oglml::TextInfo textInfo = { shader.GetProgramID(), w, h };

	auto allocator = MemoryManager::Get().GetGlobalAllocator();
	m_text = Allocate<oglml::Text>(allocator.get(), textInfo);
}

TextWidget::~TextWidget()
{
	auto allocator = MemoryManager::Get().GetGlobalAllocator();
	Deallocate<oglml::Text>(allocator.get(), m_text);
}

void TextWidget::Draw()
{
	m_updateFunc(m_text);

	m_text->Draw();
}

oglml::Text& TextWidget::GetText()
{
	return *m_text;
}

void TextWidget::SetUpdateFunc(const std::function<void(oglml::Text*)>& update)
{
	m_updateFunc = update;
}