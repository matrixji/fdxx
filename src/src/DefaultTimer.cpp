#include "DefaultTimer.hpp"
#include <sys/timerfd.h>
#include <unistd.h>
#include <cstdio>
#include "fdxx/Logger.hpp"

using fdxx::DefaultTimer;
using fdxx::LogAdapter;

DefaultTimer::DefaultTimer(long timeout, long interval, LogAdapter& logAdapter, Callback callback)
    : log_{logAdapter}, callback_{std::move(callback)}
{
    itimerspec tm{
        {interval / 1000, (interval % 1000) * 1000000},
        {timeout / 1000, (timeout % 1000) * 1000000},
    };

    fd_ = timerfd_create(CLOCK_MONOTONIC, 0);
    timerfd_settime(fd_, 0, &tm, nullptr);
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
    LOG_DEBUG(log_) << "event: " << fdxx::to_string(event) << ", fd: " << fd_;
    callback_(*this, true);
}