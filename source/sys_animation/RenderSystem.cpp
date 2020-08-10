#include <RenderSystem.h>

#include <SystemManager.h>

#include <ParticleSystem.h>
#include <SpriteRenderSystem.h>

using namespace breakout;

RenderSystem::RenderSystem()
    : BaseSystem()
{
    m_spriteRender = SystemManager::Get().CreateSystem<SpriteRenderSystem>();
    m_particleRender = SystemManager::Get().CreateSystem<ParticleRenderSystem>();
}

void RenderSystem::Init()
{
    m_spriteRender->Init();
    m_particleRender->Init();
}

void RenderSystem::Update(float dtMilliseconds)
{
    m_spriteRender->Update(dtMilliseconds);
    m_particleRender->Update(dtMilliseconds);
}

