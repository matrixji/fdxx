#pragma once
#include <memory>
#include <vector>

#include "fdxx/Event.hpp"

namespace fdxx {

class Handler;

template <typename T> class Epoll {
public:
  using Handlers = std::vector<std::unique_ptr<Handler>>;
  template <typename... Args> Epoll(Args... args) : t{std::forward(args...)} {}
  Epoll(){}

  void add(std::shared_ptr<Handler> handler, const Event event) {
    return t.add(handler, event);
  }

  void del(std::shared_ptr<Handler> handler) { return t.del(handler); }

  void process(const int milliseconds) { return t.process(milliseconds); }

private:
  T t;
};
} // namespace fdxx
