#pragma once

#include <APostEffectState.h>

namespace oglml
{
	class PostProcessor;
}

namespace breakout
{
	class ShakePostEffect : public APostEffectState
	{
	public:

		ShakePostEffect(oglml::PostProcessor* pp);

		virtual ~ShakePostEffect() override;

		virtual void Awake() override;

		virtual void Begin() override;

		virtual void End() override;

		virtual void Draw(float dtMilliseconds) override;
	};
}