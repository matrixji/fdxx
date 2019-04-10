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
    using Callback = std::function<void(Timer&, bool)>;
    std::unique_ptr<Timer> create(long timeout, long interval, LogAdapter&, Callback);
    std::unique_ptr<Timer> create(long timeout, LogAdapter&, Callback);
};
} // namespace fdxx
