#pragma once

#include <APostEffectState.h>

namespace oglml
{
	class PostProcessor;
}

namespace breakout
{
	class IdlePostEffect : public APostEffectState
	{
	public:

		IdlePostEffect(oglml::PostProcessor* pp);

		virtual ~IdlePostEffect() override;

		virtual void Awake() override;

		virtual void Begin() override;

		virtual void End() override;

		virtual void Draw() override;
	};
}