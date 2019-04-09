#pragma once
#include <functional>
#include "fdxx/Handler.hpp"

namespace fdxx
{
class LogAdapter;

class DefaultTimer : public Handler
{
public:
    using Callback = std::function<void(Handler&, bool)>;
    DefaultTimer(long, long, LogAdapter&, Callback);
    int fd() final;
    void handle(Event) final;

private:
    LogAdapter& log_;
    Callback callback_;
    int fd_{-1};
};

}