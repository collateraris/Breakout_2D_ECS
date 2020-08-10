#pragma once

#include <System.h>

namespace breakout
{
	class ParticleRenderSystem : public BaseSystem
	{

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Particle;
        }

        ParticleRenderSystem()
            : BaseSystem() {}


        virtual ~ParticleRenderSystem() {};

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;
	};
}