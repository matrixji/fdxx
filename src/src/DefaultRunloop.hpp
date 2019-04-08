#pragma once
#include "fdxx/Runloop.hpp"
#include <condition_variable>
#include <mutex>

#include "Epoll.hpp"
#include "LinuxEpoll.hpp"

namespace fdxx {
class Handler;

class DefaultRunloop : public Runloop {
public:
  DefaultRunloop(std::string name);
  DefaultRunloop(const Runloop &) = delete;
  DefaultRunloop &operator=(const DefaultRunloop &) = delete;
  virtual ~DefaultRunloop();
  void regist(std::shared_ptr<Handler>, const Event) override;
  void unregist(std::shared_ptr<Handler>) override;
  void run() override;
  void start() override;
  void stop() override;

private:
  std::string name_;
  bool running_{false};
  std::mutex mutex_{};
  std::condition_variable cond_{};
  Epoll<LinuxEpoll> epoll_{};
};
} // namespace fdxx
