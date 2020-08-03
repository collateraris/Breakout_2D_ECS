#include <MovementComponent.h>

using namespace breakout;

MovementComponent::MovementComponent()
{

}

MovementComponent::~MovementComponent()
{

}

const std::array<float, 2>& MovementComponent::GetVelocity() const
{
	return m_velocity;
}

void MovementComponent::SetVelocity(const std::array<float, 2>& velocity)
{
	m_velocity = velocity;
}

void MovementComponent::SetUpdateFunction(const std::function<void(int, int, float)>& update)
{
	m_updateFunction = update;
}

void MovementComponent::Update(float dtMilliseconds)
{
	m_updateFunction(m_entityId, m_componentId, dtMilliseconds);
}