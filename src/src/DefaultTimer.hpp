#pragma once
#include <memory>
#include "fdxx/Timer.hpp"

namespace fdxx
{
class LogAdapter;

class DefaultTimer : public Timer
{
public:
    DefaultTimer(int64_t timeout, int64_t interval, std::shared_ptr<LogAdapter> logAdapter, Callback callback);
    DefaultTimer(const DefaultTimer&) = delete;
    DefaultTimer& operator=(const DefaultTimer&) = delete;
    DefaultTimer(DefaultTimer&&) = default;
    DefaultTimer& operator=(DefaultTimer&&) = default;
    ~DefaultTimer() override;

    int fd() override;
    void handle(Event event) override;
    void cancel() override;
    void update(int64_t timeout, int64_t interval) override;
    void setCallback(Callback callback) override;

private:
    void update_(int64_t timeout, int64_t interval);
    std::shared_ptr<LogAdapter> log_;
    Callback callback_;
    int fd_{-1};
};

} // namespace fdxx