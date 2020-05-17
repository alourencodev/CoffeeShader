#ifndef COFFEE_HANDLE_HPP
#define COFFEE_HANDLE_HPP

#include <limits>

#include "Utils/Assert.hpp"

namespace coffee
{
    
#define DEFINE_HANDLE(name) struct name ## _handle{}; using name = Handle< name ## _handle >

template<typename _>
struct Handle
{
    Handle() = default;
    explicit Handle(uint16_t v)
    {
        ASSERT(v < std::numeric_limits<uint16_t>::max());
        value = v;
    }

    uint16_t value = std::numeric_limits<uint16_t>::max();

    bool operator == (const Handle &other) const { return value == other.value; }
    explicit operator uint16_t() const { return value; }
};

}

#endif