#include <ParticlesSystem.h>

#include <EntityComponentSystem.h>
#include <ParticlesComponent.h>

using namespace breakout;

void ParticlesRenderSystem::Init()
{

}

void ParticlesRenderSystem::Update(float dtMilliseconds)
{
	auto& particlesComponents = EntityComponentSystem::Get().GetAllComponentsByType<ParticlesComponent>();

	for (auto& particles : particlesComponents)
	{
		particles->GetContainer().Update(dtMilliseconds);
		particles->GetContainer().Draw();
	}
}

