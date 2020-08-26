#include <RenderSystem.h>

#include <SystemManager.h>

#include <PostEffectsStateManager.h>

#include <ParticlesSystem.h>
#include <SpriteRenderSystem.h>
#include <PostProcessorSystem.h>

using namespace breakout;

RenderSystem::RenderSystem()
    : BaseSystem()
{

}

void RenderSystem::Init()
{
    auto& sm = SystemManager::Get();
    m_spriteRender = sm.CreateSystem<SpriteRenderSystem>();
    m_particlesRender = sm.CreateSystem<ParticlesRenderSystem>();
    m_postProcessing = sm.CreateSystem<PostProcessingSystem>();

    m_spriteRender->Init();
    m_particlesRender->Init();
    m_postProcessing->Init();

    PostEffectsStateManager::Get().Init();
}

void RenderSystem::Update(float dtMilliseconds)
{
    m_postProcessing->PreUpdate(dtMilliseconds);

    m_spriteRender->Update(dtMilliseconds);
    m_particlesRender->Update(dtMilliseconds);

    m_postProcessing->Update(dtMilliseconds);
}

