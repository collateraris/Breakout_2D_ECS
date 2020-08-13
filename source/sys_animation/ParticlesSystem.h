#pragma once

#include <System.h>

namespace breakout
{
	class ParticlesRenderSystem : public BaseSystem
	{

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Particles;
        }

        ParticlesRenderSystem()
            : BaseSystem() {}


        virtual ~ParticlesRenderSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;
	};
}