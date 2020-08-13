#pragma once

#include <System.h>

namespace breakout
{
    class ParticlesRenderSystem;
    class SpriteRenderSystem;

	class RenderSystem : public BaseSystem
	{

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Render;
        }

        RenderSystem();

        virtual ~RenderSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

    private:

        ParticlesRenderSystem* m_particlesRender = nullptr;
        SpriteRenderSystem* m_spriteRender = nullptr;

	};
}