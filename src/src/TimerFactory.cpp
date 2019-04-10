#include "fdxx/TimerFactory.hpp"
#include "DefaultTimer.hpp"

using fdxx::DefaultTimer;
using fdxx::Timer;
using fdxx::TimerFactory;

std::unique_ptr<Timer> TimerFactory::create(int64_t timeout, std::shared_ptr<LogAdapter> logger, Callback callback)
{
    return std::make_unique<DefaultTimer>(timeout, 0, std::move(logger), std::move(callback));
}

std::unique_ptr<Timer> TimerFactory::create(int64_t timeout, int64_t interval, std::shared_ptr<LogAdapter> logger, Callback callback)
{
    return std::make_unique<DefaultTimer>(timeout, interval, std::move(logger), std::move(callback));
}