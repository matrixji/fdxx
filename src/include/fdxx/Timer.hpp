#pragma once

#include "Handler.hpp"

namespace fdxx
{
class Timer : public Handler
{
public:
    Timer() = default;
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = default;
    Timer& operator=(Timer&&) = default;
    ~Timer() override = default;

    virtual void cancel() = 0;
    virtual void update(int64_t timeout, int64_t interval) = 0;
};

} // namespace fdxx
