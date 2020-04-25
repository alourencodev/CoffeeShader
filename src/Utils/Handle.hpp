#ifndef COFFEE_HANDLE_HPP
#define COFFEE_HANDLE_HPP

namespace coffee
{
    
#define DEFINE_HANDLE(name) struct name ## _handle{}; using name = Handle< name ## _handle >

template<typename _>
struct Handle
{
    explicit Handle(uint16_t v): value(v) {}

    uint16_t value;

    bool operator == (const Handle &other) const { return value == other.value; }
    explicit operator uint16_t() const { return value; }
};

}

#endif