#include <posteffects/ChaosPostEffect.h>

#include <OGLML/PostProcessor.h>
#include <OGLML/Sprite.h>

#include <ShaderAssetId.h>
#include <ShadersManager.h>

namespace breakout
{
	ChaosPostEffect::ChaosPostEffect(oglml::PostProcessor* pp)
		: APostEffectState(pp)
	{
		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::ChaosPostEffect));
		GetPostProcessor()->SetShader(shader);
	}

	ChaosPostEffect::~ChaosPostEffect()
	{

	}

	void ChaosPostEffect::Awake()
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

		std::vector<int> edge_kernel =
		{
			-1, -1, -1,
			-1,  8, -1,
			-1, -1, -1
		};

		std::function<void(unsigned int)> awakeShaderParamsFun = [&](unsigned int shaderId)
		{
			oglml::Shader::Use(shaderId);

			std::string uniformOffsetStr = "uOffsets";
			oglml::Shader::SetVector2fv(shaderId, uniformOffsetStr, KERNEL_SIZE, (float*)offsets);

			std::string uniformuEdgeKernelStr = "uEdgeKernel";
			oglml::Shader::SetIntv(shaderId, uniformuEdgeKernelStr.c_str(), KERNEL_SIZE, edge_kernel.data());
		};

		GetPostProcessor()->SetShaderParams(awakeShaderParamsFun);
	}

	void ChaosPostEffect::Begin()
	{
		GetPostProcessor()->BeginRenderInFramebuffer();
	}

	void ChaosPostEffect::End()
	{
		GetPostProcessor()->EndRenderInFramebuffer();
	}

	void ChaosPostEffect::Draw(float dtMilliseconds)
	{
		GetPostProcessor()->Draw(dtMilliseconds);
	}
}