#pragma once

#include "Event.hpp"

namespace fdxx {
class Runloop;

class Handler {
public:
  Handler() = default;
  Handler(const Handler &) = delete;
  Handler &operator=(const Handler &) = delete;
  virtual ~Handler() = default;
  virtual int fd() = 0;
  virtual void handle(const Event &) = 0;
};

} // namespace fdxx
