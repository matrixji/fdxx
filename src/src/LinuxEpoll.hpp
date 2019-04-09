#pragma once
#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "fdxx/Event.hpp"

namespace fdxx
{
class Handler;

class LinuxEpoll
{
public:
    using HandlerContext = struct
    {
        std::shared_ptr<Handler> handler;
        Event event;
    };
    LinuxEpoll();
    void add(std::shared_ptr<Handler>, Event);
    void del(const std::shared_ptr<Handler>&);
    void process(int);

private:
    int epollFd_{0};
    std::unordered_map<int, HandlerContext> handlers_{};
    std::unique_ptr<struct ::epoll_event[]> events_{nullptr};
    size_t eventsSize_{0};
};
} // namespace fdxx
