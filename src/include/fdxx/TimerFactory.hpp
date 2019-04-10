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
    std::unique_ptr<Timer> create(long timeout, long interval, LogAdapter& logAdapter, Callback callback);
    std::unique_ptr<Timer> create(long timeout, LogAdapter& logAdapter, Callback callback);
};
} // namespace fdxx
