#pragma once

#include <Allocator.h>

namespace breakout
{
	class LinearAllocator : public Allocator
	{
    public:

        LinearAllocator(const size_t size);
        ~LinearAllocator() override;

        void* Allocate(const size_t size) override;
        void Deallocate(void* p) override final;

        virtual void Clear();

    protected:

        void* m_memoryStart = nullptr;
        void* m_currentPosition = nullptr;
	};
}