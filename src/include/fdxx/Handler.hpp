#pragma once

#include "Event.hpp"

namespace fdxx {
class Runloop;

class Handler {
public:
  Handler() = delete;
  Handler(const Handler &) = delete;
  Handler &operator=(const Handler &) = delete;
  virtual ~Handler() = default;
  virtual int fd() = 0;
  virtual void handle(const Event &, const Runloop &) = 0;
};

} // namespace fdxx
