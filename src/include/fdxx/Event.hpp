#pragma once

#include "Bitmask.hpp"

namespace fdxx {
enum class Event : unsigned {
  none = 0x0000,
  read = 0x0001,
  write = 0x0002,
  error = 0x0004,
  all = 0xffff,
};
}

ENABLE_BITMASK_OPERATORS(fdxx::Event)
