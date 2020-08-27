#pragma once

namespace oglml
{
	class PostProcessor;
}

namespace breakout
{
	class APostEffectState;

	class LinearAllocator;

	class PostEffectsFabric
	{
		using EnumStateName = int;
	public:

		static APostEffectState* GeneratePostEffect(LinearAllocator*, EnumStateName, oglml::PostProcessor*);
	};
}