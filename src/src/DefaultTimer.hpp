#pragma once
#include <functional>
#include "fdxx/Timer.hpp"

namespace fdxx
{
class LogAdapter;

class DefaultTimer : public Timer
{
public:
    using Callback = std::function<void(Timer&, bool)>;
    DefaultTimer(long, long, LogAdapter&, Callback);
    int fd() final;
    void handle(Event) final;
    void cancel() final;
    void update(long, long) final;

private:
    LogAdapter& log_;
    Callback callback_;
    int fd_{-1};
};

}