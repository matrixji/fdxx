#pragma once
#include <functional>
#include <memory>

namespace fdxx
{
class Handler;
class LogAdapter;

class TimerFactory
{
public:
    using Callback = std::function<void(Handler&, bool)>;
    std::unique_ptr<Handler> create(long, long, LogAdapter&, Callback);
    std::unique_ptr<Handler> create(long, LogAdapter&, Callback);
};
} // namespace fdxx
