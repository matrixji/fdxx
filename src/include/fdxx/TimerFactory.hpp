#pragma once
#include <memory>
#include "Timer.hpp"

namespace fdxx
{
class LogAdapter;

class TimerFactory
{
public:
    std::unique_ptr<Timer> create(
        int64_t timeout,
        int64_t interval,
        std::shared_ptr<LogAdapter> logAdapter,
        Timer::Callback callback);
    std::unique_ptr<Timer> create(int64_t timeout, std::shared_ptr<LogAdapter> logAdapter, Timer::Callback callback);
};
} // namespace fdxx
