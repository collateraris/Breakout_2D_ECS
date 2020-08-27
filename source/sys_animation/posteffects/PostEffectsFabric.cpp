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
		return Allocate<IdlePostEffect>(allocator, pp);
	case EPostEffectStates::Confuse:
		return Allocate<ConfusePostEffect>(allocator, pp);
	case EPostEffectStates::Chaos:
		return Allocate<ChaosPostEffect>(allocator, pp);
	case EPostEffectStates::Shake:
		return Allocate<ShakePostEffect>(allocator, pp);
	default:
		assert(false);
		return nullptr;
		break;
	}
}

