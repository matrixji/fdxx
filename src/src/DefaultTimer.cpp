#include "DefaultTimer.hpp"
#include <sys/timerfd.h>
#include <unistd.h>
#include "fdxx/Logger.hpp"

using fdxx::DefaultTimer;
using fdxx::LogAdapter;

DefaultTimer::DefaultTimer(long timeout, long interval, LogAdapter& logAdapter, Callback callback)
    : log_{logAdapter}, callback_{std::move(callback)}
{
    fd_ = timerfd_create(CLOCK_MONOTONIC, 0);
    update(timeout, interval);
}

int DefaultTimer::fd()
{
    return fd_;
}

void DefaultTimer::handle(const Event event)
{
    if (event == Event::read)
    {
        uint64_t ts;
        ::read(fd_, &ts, sizeof(ts));
    }
    callback_(true);
}

void DefaultTimer::cancel()
{
    update(0, 0);
}

void DefaultTimer::update(long timeout, long interval)
{
    itimerspec tm{
        {interval / 1000, (interval % 1000) * 1000000},
        {timeout / 1000, (timeout % 1000) * 1000000},
    };
    timerfd_settime(fd_, 0, &tm, nullptr);
}