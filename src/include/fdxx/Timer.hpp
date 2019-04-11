#pragma once
#include <functional>
#include <memory>
#include "Handler.hpp"

namespace fdxx
{
class Timer : public Handler, public std::enable_shared_from_this<Timer>
{
public:
    using Callback = std::function<void(std::shared_ptr<Timer>)>;
    Timer() = default;
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = default;
    Timer& operator=(Timer&&) = default;
    ~Timer() override = default;

    virtual void cancel() = 0;
    virtual void update(int64_t timeout, int64_t interval) = 0;
    virtual void setCallback(Callback callback) = 0;
};

} // namespace fdxx
