#include <components/TransformComponent.h>

using namespace breakout;

void TransformComponent::operator=(const TransformComponent& outer)
{
	SetPosition(outer.GetPosition());
	SetRotation(outer.GetRotation());
	SetScale(outer.GetScale());
}

const std::array<float, 2>& TransformComponent::GetPosition() const
{
	return m_position;
}

TransformComponent& TransformComponent::SetPosition(const std::array<float, 2>& newPosition)
{
	m_position = newPosition;
	return *this;
}


float TransformComponent::GetRotation() const
{
	return m_rotation;
}

TransformComponent& TransformComponent::SetRotation(float newRotation)
{
	m_rotation = newRotation;
	return *this;
}

const std::array<float, 2>& TransformComponent::GetScale() const
{
	return m_scale;
}

TransformComponent& TransformComponent::SetScale(const std::array<float, 2>& newScale)
{
	m_scale = newScale;
	return *this;
}