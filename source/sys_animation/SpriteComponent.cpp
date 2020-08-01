#include <SpriteComponent.h>

using namespace breakout;

SpriteComponent::SpriteComponent()
{

}

SpriteComponent::~SpriteComponent()
{

}

oglml::Sprite& SpriteComponent::Sprite()
{
	return m_sprite;
}