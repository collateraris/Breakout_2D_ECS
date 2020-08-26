#pragma once

namespace oglml
{
	class PostProcessor;
}

namespace breakout
{
	enum class EPostEffectStates
	{
		Idle,
		Confuse,
		Chaos,
		Shake,
		MAX
	};

	class APostEffectState
	{
	public:

		APostEffectState(oglml::PostProcessor* pp);

		virtual ~APostEffectState();

		virtual void Awake() = 0;

		virtual void Begin() = 0;

		virtual void End() = 0;

		virtual void Draw() = 0;

	protected:

		oglml::PostProcessor* GetPostProcessor();

	private:

		oglml::PostProcessor* m_postProcessor = nullptr;
	};
}
