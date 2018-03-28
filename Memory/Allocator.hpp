//
// Created by luiz0tavio on 3/28/18.
//

#ifndef ONYX_ALLOCATOR_HPP
#define ONYX_ALLOCATOR_HPP

#include <cstdlib>
#include <new>
#include <iostream>
#include <limits>
#include "Provider.hpp"

namespace Memory
{
    template <class T>
    struct Allocator {

        typedef T value_type;

        Allocator() = default;
        template <class U> constexpr
        Allocator(const Allocator<U>&) noexcept {}

        T* allocate(std::size_t size) noexcept
        {
            std::cout << "pushin " << std::to_string(size) << "bytes." << std::endl;

            auto max = std::numeric_limits<size_t>::max() / sizeof(T);
            if (size > max) {
                std::cerr << "ERR: Size: " << std::to_string(size) << "bytes exceeds max." << std::endl;
            }

            auto mem = Memory::Provider::getMemory(PoolType::POOL_TYPE_GENERIC, sizeof(T));
            if ( auto p = static_cast<T*>(mem) ) return p;

            std::cerr << "ERR: Cannot get memory. Size: " << std::to_string(size) << "bytes." << std::endl;
        }

        void deallocate(T* p, std::size_t) noexcept
        {
            //std::free(p);
        }
    };

    template <class T, class U>
    bool operator==(const Allocator<T>&, const Allocator<U>&) { return true; }

    template <class T, class U>
    bool operator!=(const Allocator<T>&, const Allocator<U>&) { return false; }
}

#endif //ONYX_ALLOCATOR_HPP