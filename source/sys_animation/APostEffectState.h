#pragma once

namespace oglml
{
	class PostProcessor;
}

namespace breakout
{
	enum class EPostEffectStates
	{
		Idle = 0,
		Confuse = 1,
		Chaos = 2,
		Shake = 3,
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

		virtual void Draw(float dtMilliseconds) = 0;

	protected:

		oglml::PostProcessor* GetPostProcessor();

	private:

		oglml::PostProcessor* m_postProcessor = nullptr;
	};
}
