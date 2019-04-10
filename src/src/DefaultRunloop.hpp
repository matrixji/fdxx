#pragma once
#include <condition_variable>
#include <mutex>
#include "fdxx/Runloop.hpp"
#include "Epoll.hpp"
#include "LinuxEpoll.hpp"

namespace fdxx
{
class Handler;
class LogAdapter;

class DefaultRunloop : public Runloop
{
public:
    DefaultRunloop(std::string name, LogAdapter& logAdapter);
    DefaultRunloop(const Runloop&) = delete;
    DefaultRunloop& operator=(const DefaultRunloop&) = delete;
    ~DefaultRunloop() override;
    void add(Handler&, Event) override;
    void remove(Handler&) override;
    void run() override;
    void start() override;
    void stop() override;

private:
    std::string name_;
    bool running_{false};
    std::mutex mutex_{};
    std::condition_variable cond_{};
    LogAdapter& log_;
    Epoll<LinuxEpoll> epoll_{log_};
};
} // namespace fdxx
