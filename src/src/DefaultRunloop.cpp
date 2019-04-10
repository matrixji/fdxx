#include "DefaultRunloop.hpp"
#include "fdxx/Logger.hpp"

using fdxx::DefaultRunloop;
using fdxx::Event;
using fdxx::Handler;
using fdxx::LogAdapter;

DefaultRunloop::DefaultRunloop(std::string name, std::shared_ptr<LogAdapter> logAdapter)
    : name_(std::move(name)), log_{std::move(logAdapter)}, epoll_{log_}
{
}

DefaultRunloop::~DefaultRunloop()
{
    stop();
}

void DefaultRunloop::start()
{
    LOG_INFO(log_) << "runner: " << name_ << "starting ...";
    std::thread th([this]() { run(); });
    th.swap(th_);
}

void DefaultRunloop::stop()
{
    if (running_)
    {
        LOG_INFO(log_) << "runner: " << name_ << "stopping ...";
        running_ = false;
        th_.join();
    }
}

void DefaultRunloop::run()
{
    constexpr int pollingTime{100};
    running_ = true;
    while (running_)
    {
        epoll_.process(pollingTime);
    }
}

void DefaultRunloop::add(std::shared_ptr<Handler> handler, const Event event)
{
    return epoll_.add(std::move(handler), event);
}

void DefaultRunloop::remove(const Handler& handler)
{
    return epoll_.del(handler);
}
