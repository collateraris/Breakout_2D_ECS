#include <posteffects/ShakePostEffect.h>

#include <OGLML/PostProcessor.h>
#include <OGLML/Sprite.h>

#include <ShaderAssetId.h>
#include <ShadersManager.h>

#include <functional>
#include <vector>

namespace breakout
{
	ShakePostEffect::ShakePostEffect(oglml::PostProcessor* pp)
		: APostEffectState(pp)
	{
		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::ShakePostEffect));
		GetPostProcessor()->SetShader(shader);
	}

	ShakePostEffect::~ShakePostEffect()
	{

	}

	void ShakePostEffect::Awake()
	{
		float offset = 1.0f / 300.0f;
		const int KERNEL_SIZE = 9;
		float offsets[KERNEL_SIZE][2] = 
		{
			{ -offset,  offset  },  // top-left
			{  0.0f,    offset  },  // top-center
			{  offset,  offset  },  // top-right
			{ -offset,  0.0f    },  // center-left
			{  0.0f,    0.0f    },  // center-center
			{  offset,  0.0f    },  // center - right
			{ -offset, -offset  },  // bottom-left
			{  0.0f,   -offset  },  // bottom-center
			{  offset, -offset  }   // bottom-right    
		};

		std::vector<float> blur_kernel =
		{
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
			2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
		};

		std::function<void(unsigned int)> awakeShaderParamsFun = [&](unsigned int shaderId)
		{
			oglml::Shader::Use(shaderId);

			std::string uniformOffsetStr = "uOffsets";
			oglml::Shader::SetVector2fv(shaderId, uniformOffsetStr, KERNEL_SIZE, (float*)offsets);

			std::string uniformuBlurKernelStr = "uBlurKernel";
			oglml::Shader::SetFloatv(shaderId, uniformuBlurKernelStr.c_str(), KERNEL_SIZE, blur_kernel.data());
		};

		GetPostProcessor()->SetShaderParams(awakeShaderParamsFun);
	}

	void ShakePostEffect::Begin()
	{
		GetPostProcessor()->BeginRenderInFramebuffer();
	}

	void ShakePostEffect::End()
	{
		GetPostProcessor()->EndRenderInFramebuffer();
	}

	void ShakePostEffect::Draw(float dtMilliseconds)
	{
		GetPostProcessor()->Draw(dtMilliseconds);
	}
}