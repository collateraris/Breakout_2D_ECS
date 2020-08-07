#pragma once

#include <System.h>

namespace breakout
{

    class CollisionSystem : public BaseSystem
    {

    public:

        static EBaseSystemType GetType()
        {
            return EBaseSystemType::Collision;
        }

        CollisionSystem();

        virtual ~CollisionSystem();

        virtual void Init() override;
        virtual void Update(float dtMilliseconds) override;

    protected:

        void CollisitionDetection(float dtMilliseconds);

    };
}