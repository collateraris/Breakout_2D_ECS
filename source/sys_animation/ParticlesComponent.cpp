#include <ParticlesComponent.h>

#include <OGLML/Shader.h>
#include <OGLML/Texture2D.h>

#include <EntityComponentSystem.h>
#include <components/TransformComponent.h>
#include <MovementComponent.h>

#include <cassert>
#include <random>

using namespace breakout;

ParticlesComponent::ParticlesComponent()
{
	Resize();
}

ParticlesComponent::~ParticlesComponent()
{

}

void ParticlesComponent::RespawnParticle(unsigned int number, const OffsetsData& offset)
{
	auto& entityTransform = EntityComponentSystem::Get().GetComponentByEntityId<TransformComponent>(m_entityId);
	auto& entityPosition = entityTransform.GetPosition();

	auto& entityMovement = EntityComponentSystem::Get().GetComponentByEntityId<MovementComponent>(m_entityId);
	auto& entityVelocity = entityMovement.GetVelocity();

	for (int i = 0; i < number; ++i)
	{
		unsigned int nextIndex = m_lifes.GetNextElementIndex();
		m_lifes.Next() = 1.0f;

		float rPos = ((rand() % 100) - 50) / 10.0f;
		float rColor = 0.5f + ((rand() % 100) / 100.0f);

		m_colors[nextIndex] = { rColor, rColor, rColor, 1.0f};

		m_velocities[nextIndex] = {entityVelocity[0] * 0.1f, entityVelocity[1] * 0.1f };

		m_positions[nextIndex] = {entityPosition[0] + rPos + offset[0], entityPosition[1] + rPos + offset[1] };

	}
}

void ParticlesComponent::Draw()
{
	m_particles.Draw();
}

void ParticlesComponent::Update(float dtMilliseconds)
{
	for (int i = 0; i < m_particlesNumber; ++i)
	{
		float& life = m_lifes.GetElement(i);
		life -= dtMilliseconds * 3.f;

		if (life > 0.f)
		{
			std::array<float, 2>& pos = m_positions[i];
			std::array<float, 2>& velocity = m_velocities[i];
			pos[0] -= velocity[0] * dtMilliseconds;
			pos[1] -= velocity[1] * dtMilliseconds;
			m_colors[i][3] -= dtMilliseconds; // alpha
		}
		else
		{
			life = 0.f;
			m_colors[i] = {0.f, 0.f, 0.f, 0.f};
		}
	}

	m_particles.BufferColorsData(m_colors);
	m_particles.BufferOffsetsData(m_positions);
}

void ParticlesComponent::SetTexture(oglml::Texture2D& texture)
{
	m_particles.SetTexture(texture);
}

void ParticlesComponent::SetShader(oglml::Shader& shader)
{
	m_particles.SetShader(shader);
}

void ParticlesComponent::Resize()
{
	m_colors.resize(m_particlesNumber, {1.f, 1.f, 1.f});
	m_positions.resize(m_particlesNumber, {0.f, 0.f});
	m_velocities.resize(m_particlesNumber, { 0.f, 0.f });
	auto& lifes = m_lifes.GetPoolElements();
	for (auto& life : lifes)
	{
		life = 0.f;
	}

	m_particles.SetNumber(m_particlesNumber);
}

void ParticlesComponent::SetOrthoParams(float width, float height)
{
	m_particles.SetOrthoParams(width, height);
}