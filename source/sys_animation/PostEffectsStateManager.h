#pragma once

#include <unordered_map>

namespace oglml
{
	class PostProcessor;
}

namespace breakout
{
	class APostEffectState;

	class PostEffectsStateManager
	{
		using EnumStateName = int;

	public:

		static PostEffectsStateManager& Get();

		void Init();

		void Begin();

		void End();

		void Draw(float dtMilliseconds);

		void SwitchState(EnumStateName state);

		bool IsActiveState(EnumStateName stateId) const;

	private:

		PostEffectsStateManager();
		~PostEffectsStateManager();
		PostEffectsStateManager(PostEffectsStateManager&) = delete;
		PostEffectsStateManager(PostEffectsStateManager&&) = delete;
		void operator=(PostEffectsStateManager&) = delete;
		void operator=(PostEffectsStateManager&&) = delete;

		std::unordered_map<EnumStateName, APostEffectState*> m_states = {};

		APostEffectState* m_currState = nullptr;
		EnumStateName m_currStateType = -1;

		oglml::PostProcessor* m_postProcessor = nullptr;
	};
}