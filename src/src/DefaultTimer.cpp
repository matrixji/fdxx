#include "DefaultTimer.hpp"
#include <sys/timerfd.h>
#include <unistd.h>
#include "fdxx/Logger.hpp"

using fdxx::DefaultTimer;
using fdxx::LogAdapter;

DefaultTimer::DefaultTimer(int64_t timeout, int64_t interval, std::shared_ptr<LogAdapter> logAdapter, Callback callback)
    : log_{std::move(logAdapter)}, callback_{std::move(callback)}
{
    fd_ = timerfd_create(CLOCK_MONOTONIC, 0);
    update(timeout, interval);
}

int DefaultTimer::fd() const
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

void DefaultTimer::update(int64_t timeout, int64_t interval)
{
    constexpr int64_t msInSec{1000};
    constexpr int64_t nsInMs{1000000};
    itimerspec tm{
        {interval / msInSec, (interval % msInSec) * nsInMs},
        {timeout / msInSec, (timeout % msInSec) * nsInMs},
    };
    timerfd_settime(fd_, 0, &tm, nullptr);
}