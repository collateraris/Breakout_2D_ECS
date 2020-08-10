#pragma once

#include <System.h>

namespace breakout
{
    class ParticleRenderSystem;
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

        ParticleRenderSystem* m_particleRender = nullptr;
        SpriteRenderSystem* m_spriteRender = nullptr;

	};
}