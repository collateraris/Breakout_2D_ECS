#include <ParticlesComponent.h>

#include <OGLML/Shader.h>
#include <OGLML/Texture2D.h>

#include <EntityComponentSystem.h>

#include <cassert>

using namespace breakout;

ParticlesComponent::ParticlesComponent()
{

}

ParticlesComponent::~ParticlesComponent()
{

}

oglml::Particles& ParticlesComponent::Particles()
{
	return m_particles;
}

void ParticlesComponent::RespawnParticle(entityId id)
{

	auto& ecs = EntityComponentSystem::Get();

}

void ParticlesComponent::SetNumber(int size)
{
	assert(size > 0);

	Particles().SetNumber(static_cast<size_t>(size));
	Resize();
}

void ParticlesComponent::SetTexture(oglml::Texture2D& texture)
{
	Particles().SetTexture(texture);
}

void ParticlesComponent::SetShader(oglml::Shader& shader)
{
	Particles().SetShader(shader);
}

void ParticlesComponent::Resize()
{
	m_colors.resize(m_particlesNumber, {1.f, 1.f, 1.f});
	m_offsets.resize(m_particlesNumber, {0.f, 0.f});
	m_velocities.resize(m_particlesNumber, { 0.f, 0.f });;
	m_life.resize(m_particlesNumber, 0.f);
}