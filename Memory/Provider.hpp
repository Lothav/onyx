//
// Created by luiz0tavio on 3/28/18.
//

#ifndef ONYX_PROVIDER_HPP
#define ONYX_PROVIDER_HPP

#include <map>
#include "Pool.hpp"

namespace Memory
{
    class Provider
    {
    public:
        static std::map<PoolType, Pool*> PoolMap;
        static void initPool();
        static void* getMemory(Memory::PoolType type, unsigned int size);
        static void destroyPool();
    };
}


#endif //ONYX_PROVIDER_HPP
