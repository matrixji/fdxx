#pragma once
#include <functional>
#include <memory>

namespace fdxx
{
class Timer;
class LogAdapter;

class TimerFactory
{
public:
    using Callback = std::function<void(bool isExpire)>;
    std::unique_ptr<Timer> create(int64_t timeout, int64_t interval, std::shared_ptr<LogAdapter> logAdapter, Callback callback);
    std::unique_ptr<Timer> create(int64_t timeout, std::shared_ptr<LogAdapter> logAdapter, Callback callback);
};
} // namespace fdxx
