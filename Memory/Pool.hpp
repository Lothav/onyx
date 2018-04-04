#ifndef ONYX_POOL_HPP
#define ONYX_POOL_HPP

#include <malloc.h>
#include <iostream>
#include <cstring>


namespace Memory
{
    enum PoolType {
        POOL_TYPE_GENERIC,
        POOL_TYPE_PLAYER,
        POOL_TYPE_MESHES
    };

    class Pool
    {

    private:

        void* mem_pool_;
        unsigned int pos_;
        PoolType type_;
        std::size_t size_;

    public:

        Pool(PoolType type, std::size_t size);
        void* get(std::size_t);
        void destroy();

    };
}

#endif //ONYX_POOL_HPP
