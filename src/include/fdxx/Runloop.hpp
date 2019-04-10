#pragma once
#include <memory>
#include "Event.hpp"

namespace fdxx
{
class Handler;

class Runloop
{
public:
    Runloop() = default;
    Runloop(const Runloop&) = delete;
    Runloop& operator=(const Runloop&) = delete;
    virtual ~Runloop() = default;
    virtual void add(Handler&, Event) = 0;
    virtual void remove(Handler&) = 0;
    virtual void run() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};
} // namespace fdxx
