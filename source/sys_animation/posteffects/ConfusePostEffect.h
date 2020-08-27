#pragma once

#include <APostEffectState.h>

namespace oglml
{
	class PostProcessor;
}

namespace breakout
{
	class ConfusePostEffect : public APostEffectState
	{
	public:

		ConfusePostEffect(oglml::PostProcessor* pp);

		virtual ~ConfusePostEffect() override;

		virtual void Awake() override;

		virtual void Begin() override;

		virtual void End() override;

		virtual void Draw(float dtMilliseconds) override;
	};
}