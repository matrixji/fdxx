#pragma once
#include "Event.hpp"

namespace fdxx
{
class Handler
{
public:
    Handler() = default;
    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;
    virtual ~Handler() = default;
    virtual int fd() = 0;
    virtual void handle(Event event) = 0;
};

} // namespace fdxx
