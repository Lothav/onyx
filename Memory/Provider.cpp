#include "Provider.hpp"

void Memory::Provider::initPools()
{
    for (auto& poolInfo: PoolsInfo) {
        _poolMap[poolInfo.type] = new Memory::Pool(poolInfo.type, poolInfo.size);
    }
}

void* Memory::Provider::getMemory(Memory::PoolType type, std::size_t size)
{
    return _poolMap[type]->get(size);
}

void Memory::Provider::destroyPools () noexcept
{
    for(auto& pool : _poolMap) {
        pool.second->destroy();
    }
};

