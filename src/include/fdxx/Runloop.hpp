#pragma once
#include "Event.hpp"
#include <memory>

namespace fdxx {
class Handler;

class Runloop {
public:
  Runloop() = default;
  Runloop(const Runloop &) = delete;
  Runloop &operator=(const Runloop &) = delete;
  virtual ~Runloop() = default;
  virtual void regist(std::shared_ptr<Handler>, const Event) = 0;
  virtual void unregist(std::shared_ptr<Handler>) = 0;
  virtual void run() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
};
} // namespace fdxx
