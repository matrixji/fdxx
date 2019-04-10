#pragma once
#include <functional>
#include <memory>
#include "fdxx/Timer.hpp"

namespace fdxx
{
class LogAdapter;

class DefaultTimer : public Timer
{
public:
    using Callback = std::function<void(bool)>;
    DefaultTimer(int64_t timeout, int64_t interval, std::shared_ptr<LogAdapter> logAdapter, Callback callback);
    int fd() const final;
    void handle(Event event) final;
    void cancel() final;
    void update(int64_t timeout, int64_t interval) final;

private:
    std::shared_ptr<LogAdapter> log_;
    Callback callback_;
    int fd_{-1};
};

} // namespace fdxx