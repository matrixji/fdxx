#pragma once

#include "Handler.hpp"

namespace fdxx
{
class Timer : public Handler
{
public:
    ~Timer() override = default;

    virtual void cancel() = 0;
    virtual void update(long timeout, long interval) = 0;
};

} // namespace fdxx
