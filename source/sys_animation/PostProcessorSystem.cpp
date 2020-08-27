#include <PostProcessorSystem.h>

#include <PostEffectsStateManager.h>

using namespace breakout;

void PostProcessingSystem::Init()
{

}

void PostProcessingSystem::PreUpdate(float dtMilliseconds)
{
	PostEffectsStateManager::Get().Begin();
}

void PostProcessingSystem::Update(float dtMilliseconds)
{
	PostEffectsStateManager::Get().End();
	PostEffectsStateManager::Get().Draw(dtMilliseconds);
}

