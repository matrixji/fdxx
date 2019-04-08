#pragma once
#include "fdxx/Runloop.hpp"
#include <condition_variable>
#include <mutex>

namespace fdxx {
class Handler;

class DefaultRunloop : public Runloop {
public:
  DefaultRunloop(std::string name);
  DefaultRunloop(const Runloop &) = delete;
  DefaultRunloop &operator=(const DefaultRunloop &) = delete;
  virtual ~DefaultRunloop();
  void regist(const Handler &, const Event) override;
  void unregist(const Handler &) override;
  void run() override;
  void start() override;
  void stop() override;

private:
  std::string name_;
  bool running_{false};
  std::mutex mutex_;
  std::condition_variable cond_;
};
} // namespace fdxx
