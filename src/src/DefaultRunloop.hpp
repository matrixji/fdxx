#pragma once
#include <memory>
#include <thread>
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
    DefaultRunloop(const DefaultRunloop&) = delete;
    DefaultRunloop& operator=(const DefaultRunloop&) = delete;
    DefaultRunloop(DefaultRunloop&&) = default;
    DefaultRunloop& operator=(DefaultRunloop&&) = default;
    ~DefaultRunloop() final;

    void add(std::shared_ptr<Handler> handler, Event event) override;
    void del(std::shared_ptr<Handler> handler) override;
    void run() override;
    void start() override;
    void stop() override;

private:
    std::string name_;
    bool running_{false};
    std::shared_ptr<LogAdapter> log_;
    Poll<LinuxEpoll> epoll_;
    std::thread th_;
};
} // namespace fdxx
