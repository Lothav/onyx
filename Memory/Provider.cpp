//
// Created by luiz0tavio on 3/28/18.
//

#include "Provider.hpp"

std::map<Memory::PoolType, Memory::Pool*> Memory::Provider::PoolMap = {};

void Memory::Provider::initPool()
{
    PoolMap[PoolType::POOL_TYPE_GENERIC] = new Memory::Pool(PoolType::POOL_TYPE_GENERIC, 500000);
}

void* Memory::Provider::getMemory(Memory::PoolType type, std::size_t size)
{
    return PoolMap[type]->get(size);
}

void Memory::Provider::destroyPool ()
{
    for(auto& pool : PoolMap) {
        pool.second->destroy();
    }
};

