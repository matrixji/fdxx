#pragma once
#include <condition_variable>
#include <memory>
#include <mutex>
#include "fdxx/Runloop.hpp"
#include "LinuxEpoll.hpp"
#include "Poll.hpp"

namespace fdxx
{
class Handler;
class LogAdapter;

class DefaultRunloop : public Runloop
{
public:
    DefaultRunloop(std::string name, std::shared_ptr<LogAdapter> logAdapter);
    ~DefaultRunloop() final;

    void add(Handler& handler, Event event) override;
    void remove(Handler& handler) override;
    void run() override;
    void start() override;
    void stop() override;

private:
    std::string name_;
    bool running_{false};
    std::mutex mutex_{};
    std::condition_variable cond_{};
    std::shared_ptr<LogAdapter> log_;
    Poll<LinuxEpoll> epoll_;
};
} // namespace fdxx
