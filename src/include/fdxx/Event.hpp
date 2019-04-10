#pragma once
#include <string>
#include "BitMask.hpp"

namespace fdxx
{
enum class Event : unsigned
{
    none = 0x0000,
    read = 0x0001,
    write = 0x0002,
    error = 0x0004,
    all = 0xffff,
};

std::string to_string(fdxx::Event event);
} // namespace fdxx

ENABLE_BIT_MASK_OPERATORS(fdxx::Event)
