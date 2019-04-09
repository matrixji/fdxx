#pragma once
#include <memory>
#include <vector>

#include "fdxx/Event.hpp"

namespace fdxx
{
class Handler;

template <typename T>
class Epoll
{
public:
    using Handlers = std::vector<std::unique_ptr<Handler>>;

    Epoll() = default;

    template <typename... Args>
    explicit Epoll(Args&&... args) : t{std::forward<Args>(args)...}
    {
    }

    void add(std::shared_ptr<Handler> handler, const Event event) { return t.add(std::move(handler), event); }

    void del(const std::shared_ptr<Handler>& handler) { return t.del(handler); }

    void process(const int milliseconds) { return t.process(milliseconds); }

private:
    T t;
};
} // namespace fdxx
