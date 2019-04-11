#pragma once
#include <memory>
#include <vector>

#include "fdxx/Event.hpp"

namespace fdxx
{
class Handler;

template <typename T>
class Poll
{
public:
    Poll() = default;

    template <typename... Args>
    explicit Poll(Args&&... args) : t{std::forward<Args>(args)...}
    {
    }

    void add(std::shared_ptr<Handler> handler, const Event event) { return t.add(std::move(handler), event); }

    void del(std::shared_ptr<Handler> handler) { return t.del(std::move(handler)); }

    void process(const int milliseconds) { return t.process(milliseconds); }

private:
    T t;
};
} // namespace fdxx
