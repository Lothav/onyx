#ifndef ONYX_MEMORYPOOL_HPP
#define ONYX_MEMORYPOOL_HPP

#include <malloc.h>
#include <iostream>
#include <cstring>

#define MEMORY_POOL_SIZE 500000

namespace Renderer
{
    class MemoryPool
    {

    public:

        static void* mem_pool_;
        static unsigned int pos_;

        static void* get(unsigned int size)
        {
            if (mem_pool_ == nullptr) {
                std::cerr << "Memory pool not allocated" << std::endl;
            }
            if (pos_+size > MEMORY_POOL_SIZE) {
                pos_ = 0;
            }
            void *pointer = (uint8_t*)mem_pool_+pos_;
            pos_ += size;
            return pointer;
        }

        static void create()
        {
            mem_pool_ = malloc(MEMORY_POOL_SIZE);
            if (mem_pool_ == nullptr) {
                std::cerr << "Error malloc memory pool" << std::endl;
            }
        }

        static void destroy()
        {
            std::free(mem_pool_);
        }

    };

    void* MemoryPool::mem_pool_ = nullptr;
    unsigned int MemoryPool::pos_ = 0;
}

#endif //ONYX_MEMORYPOOL_HPP
