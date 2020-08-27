#pragma once

#include <System.h>

namespace breakout
{
    class PostProcessingSystem : public BaseSystem
    {

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::PostProcessing;
        }

        PostProcessingSystem()
            : BaseSystem() {}


        virtual ~PostProcessingSystem() {};

        virtual void Init() override;
        void PreUpdate(float dtMilliseconds);
        virtual void Update(float dtMilliseconds) override;


    };
}