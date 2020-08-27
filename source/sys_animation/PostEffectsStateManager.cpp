#include <PostEffectsStateManager.h>

#include <OGLML/PostProcessor.h>

#include <MemoryManager.h>
#include <LinearAllocator.h>

#include <gameContext.h>

#include <APostEffectState.h>
#include <posteffects/PostEffectsFabric.h>

#include <cassert>

using namespace breakout;

PostEffectsStateManager::PostEffectsStateManager()
{
	
}

PostEffectsStateManager::~PostEffectsStateManager()
{

}

PostEffectsStateManager& PostEffectsStateManager::Get()
{
	static PostEffectsStateManager postEffectsStateManager;
	return postEffectsStateManager;
}

void PostEffectsStateManager::Init()
{
	auto globalAllocator = MemoryManager::Get().GetGlobalAllocator();
	m_postProcessor = Allocate<oglml::PostProcessor>(globalAllocator.get());

	int windowW, windowH;
	GameContext::Get().GetMainWindowSize(windowW, windowH);
	m_postProcessor->Init(windowW, windowH);

	SwitchState(static_cast<int>(EPostEffectStates::Chaos));
}

void PostEffectsStateManager::Begin()
{
	assert(m_currState != nullptr);
	m_currState->Begin();
}

void PostEffectsStateManager::End()
{
	assert(m_currState != nullptr);
	m_currState->End();
}

void PostEffectsStateManager::Draw(float dtMilliseconds)
{
	assert(m_currState != nullptr);
	m_currState->Draw(dtMilliseconds);
}

void PostEffectsStateManager::SwitchState(EnumStateName stateId)
{
	assert(m_postProcessor != nullptr);

	auto& foundIt = m_states.find(stateId);
	if (foundIt == m_states.end())
	{
		auto allocator = MemoryManager::Get().GetGlobalAllocator();
		auto newState = PostEffectsFabric::GeneratePostEffect(allocator.get(), stateId, m_postProcessor);
		m_states.insert({stateId, newState});
	}

	m_currState = m_states[stateId];

	m_currState->Awake();
}