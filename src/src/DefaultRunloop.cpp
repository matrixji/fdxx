#include "DefaultRunloop.hpp"
#include <iostream>
#include <thread>

using fdxx::DefaultRunloop;
using fdxx::Event;
using fdxx::Handler;

DefaultRunloop::DefaultRunloop(std::string name) : name_(std::move(name)) {}

DefaultRunloop::~DefaultRunloop() { stop(); }

void DefaultRunloop::start() {
  std::cout << "starting ..." << std::endl;
  std::thread th([this]() { run(); });
  th.detach();
}

void DefaultRunloop::stop() {
  if (running_) {
    std::cout << "stoping ..." << std::endl;
    std::unique_lock<std::mutex> lock{mutex_};
    running_ = false;
    cond_.wait(lock);
  }
}

void DefaultRunloop::run() {
  running_ = true;
  while (running_) {
      epoll_.process(100);
  }
  std::unique_lock<std::mutex> lock{mutex_};
  cond_.notify_one();
}

void DefaultRunloop::regist(std::shared_ptr<Handler> handler, const Event event) {
    return epoll_.add(handler, event);
}
void DefaultRunloop::unregist(std::shared_ptr<Handler> handler) {
    return epoll_.del(handler);
}
