#include <RenderSystem.h>

#include <SystemManager.h>

#include <ParticlesSystem.h>
#include <SpriteRenderSystem.h>

using namespace breakout;

RenderSystem::RenderSystem()
    : BaseSystem()
{
    m_spriteRender = SystemManager::Get().CreateSystem<SpriteRenderSystem>();
    m_particlesRender = SystemManager::Get().CreateSystem<ParticlesRenderSystem>();
}

void RenderSystem::Init()
{
    m_spriteRender->Init();
    m_particlesRender->Init();
}

void RenderSystem::Update(float dtMilliseconds)
{
    m_spriteRender->Update(dtMilliseconds);
    m_particlesRender->Update(dtMilliseconds);
}

