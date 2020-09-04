#include <posteffects/PostEffectsFabric.h>

#include <APostEffectState.h>
#include <posteffects/IdlePostEffect.h>
#include <posteffects/ChaosPostEffect.h>
#include <posteffects/ConfusePostEffect.h>
#include <posteffects/ShakePostEffect.h>

#include <MemoryManager.h>
#include <LinearAllocator.h>

#include <cassert>

using namespace breakout;

APostEffectState* PostEffectsFabric::GeneratePostEffect(LinearAllocator* allocator, EnumStateName state, oglml::PostProcessor* pp)
{
	EPostEffectStates stateId = static_cast<EPostEffectStates>(state);

	switch (stateId)
	{
	case EPostEffectStates::Idle:
		return allocate<IdlePostEffect>(allocator, pp);
	case EPostEffectStates::Confuse:
		return allocate<ConfusePostEffect>(allocator, pp);
	case EPostEffectStates::Chaos:
		return allocate<ChaosPostEffect>(allocator, pp);
	case EPostEffectStates::Shake:
		return allocate<ShakePostEffect>(allocator, pp);
	default:
		assert(false);
		return nullptr;
		break;
	}
}

