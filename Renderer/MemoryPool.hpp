#ifndef ONYX_MEMORYPOOL_HPP
#define ONYX_MEMORYPOOL_HPP

#include <malloc.h>
#include <iostream>

#define MEMORY_POOL_SIZE 500000

namespace Renderer
{
    class MemoryPool
    {
    public:

        static void* mem_pool_;

        static void* getPool()
        {
            if (mem_pool_ == nullptr) {
                std::cerr << "Memory pool not allocated" << std::endl;
            }
            return mem_pool_;
        }

        static void createPool()
        {
            mem_pool_ = malloc(MEMORY_POOL_SIZE);
            if (mem_pool_ == nullptr) {
                std::cerr << "Error malloc memory pool" << std::endl;
            }
        }

    };

    void * MemoryPool::mem_pool_ = nullptr;
}


#endif //ONYX_MEMORYPOOL_HPP
