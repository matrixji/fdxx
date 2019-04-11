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
    Runloop(Runloop&&) = default;
    Runloop& operator=(Runloop&&) = default;
    virtual ~Runloop() = default;
    virtual void add(std::shared_ptr<Handler> handler, Event event) = 0;
    virtual void del(std::shared_ptr<Handler> handler) = 0;
    virtual void run() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};
} // namespace fdxx
