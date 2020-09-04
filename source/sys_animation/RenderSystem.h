#pragma once

#include <System.h>

namespace breakout
{
    class ParticlesRenderSystem;
    class SpriteRenderSystem;
    class PostProcessingSystem;
    class GuiSystem;

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
        PostProcessingSystem* m_postProcessing = nullptr;
        GuiSystem* m_gui = nullptr;
	};
}