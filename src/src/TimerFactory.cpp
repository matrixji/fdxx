#include "fdxx/TimerFactory.hpp"
#include "DefaultTimer.hpp"

using fdxx::DefaultTimer;
using fdxx::Timer;
using fdxx::TimerFactory;

std::unique_ptr<Timer> TimerFactory::create(long timeout, LogAdapter& logger, Callback callback)
{
    return std::make_unique<DefaultTimer>(timeout, 0, logger, std::move(callback));
}

std::unique_ptr<Timer> TimerFactory::create(long timeout, long interval, LogAdapter& logger, Callback callback)
{
    return std::make_unique<DefaultTimer>(timeout, interval, logger, std::move(callback));
}