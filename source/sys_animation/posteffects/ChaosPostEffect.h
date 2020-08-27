#pragma once

#include <APostEffectState.h>

namespace oglml
{
	class PostProcessor;
}

namespace breakout
{
	class ChaosPostEffect : public APostEffectState
	{
	public:

		ChaosPostEffect(oglml::PostProcessor* pp);

		virtual ~ChaosPostEffect() override;

		virtual void Awake() override;

		virtual void Begin() override;

		virtual void End() override;

		virtual void Draw(float dtMilliseconds) override;
	};
}