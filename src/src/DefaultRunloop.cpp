#include "DefaultRunloop.hpp"
#include <thread>
#include "fdxx/Logger.hpp"

using fdxx::DefaultRunloop;
using fdxx::Event;
using fdxx::Handler;
using fdxx::LogAdapter;

DefaultRunloop::DefaultRunloop(std::string name, LogAdapter& logAdapter) : name_(std::move(name)), log_{logAdapter} {}

DefaultRunloop::~DefaultRunloop()
{
    stop();
}

void DefaultRunloop::start()
{
    LOG_INFO(log_) << "starting ...";
    std::thread th([this]() { run(); });
    th.detach();
}

void DefaultRunloop::stop()
{
    if (running_)
    {
        LOG_INFO(log_) << "stopping ...";
        std::unique_lock<std::mutex> lock{mutex_};
        running_ = false;
        cond_.wait(lock);
    }
}

void DefaultRunloop::run()
{
    running_ = true;
    while (running_)
    {
        epoll_.process(100);
    }
    std::unique_lock<std::mutex> lock{mutex_};
    cond_.notify_one();
}

void DefaultRunloop::add(std::shared_ptr<Handler> handler, const Event event)
{
    return epoll_.add(handler, event);
}

void DefaultRunloop::remove(std::shared_ptr<Handler> handler)
{
    return epoll_.del(handler);
}
