#include <APostEffectState.h>

#include <OGLML/PostProcessor.h>

#include <cassert>

using namespace breakout;

APostEffectState::APostEffectState(oglml::PostProcessor* pp)
{
	m_postProcessor = pp;
}

APostEffectState::~APostEffectState() {};

oglml::PostProcessor* APostEffectState::GetPostProcessor()
{
	assert(m_postProcessor != nullptr);
	return m_postProcessor;
}