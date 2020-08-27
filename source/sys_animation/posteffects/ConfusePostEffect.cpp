#include <posteffects/ConfusePostEffect.h>

#include <OGLML/PostProcessor.h>
#include <OGLML/Sprite.h>

#include <ShaderAssetId.h>
#include <ShadersManager.h>

namespace breakout
{
	ConfusePostEffect::ConfusePostEffect(oglml::PostProcessor* pp)
		: APostEffectState(pp)
	{
		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::ConfusePostEffect));
		GetPostProcessor()->SetShader(shader);
	}

	ConfusePostEffect::~ConfusePostEffect()
	{

	}

	void ConfusePostEffect::Awake()
	{

	}

	void ConfusePostEffect::Begin()
	{
		GetPostProcessor()->BeginRenderInFramebuffer();
	}

	void ConfusePostEffect::End()
	{
		GetPostProcessor()->EndRenderInFramebuffer();
	}

	void ConfusePostEffect::Draw(float dtMilliseconds)
	{
		GetPostProcessor()->Draw(dtMilliseconds);
	}
}