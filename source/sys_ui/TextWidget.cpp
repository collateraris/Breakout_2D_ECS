#include <TextWidget.h>

#include <MemoryManager.h>

#include <OGLML/Text.h>

using namespace breakout;

TextWidget::TextWidget()
{
	auto allocator = MemoryManager::Get().GetGlobalAllocator();
	m_text = Allocate<oglml::Text>(allocator.get());
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