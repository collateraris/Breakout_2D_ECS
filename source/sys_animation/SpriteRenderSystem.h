#pragma once

#include <System.h>

namespace breakout
{
	class SpriteRenderSystem : public BaseSystem
	{

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::SpriteRender;
        }

        SpriteRenderSystem()
            : BaseSystem() {}


        virtual ~SpriteRenderSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

        void Render();

	};
}