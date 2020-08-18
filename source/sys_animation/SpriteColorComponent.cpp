#include <SpriteColorComponent.h>

using namespace breakout;

SpriteColorComponent::SpriteColorComponent()
{

}

SpriteColorComponent::~SpriteColorComponent()
{

}


void SpriteColorComponent::SetColor(const std::array<float, 3>& color)
{
	m_color = color;
}

const std::array<float, 3>& SpriteColorComponent::GetColor() const
{
	return m_color;
}