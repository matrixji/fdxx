#pragma once
#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "fdxx/Event.hpp"

namespace fdxx
{
class Handler;
class LogAdapter;

class LinuxEpoll
{
public:
    using HandlerContext = struct
    {
        Handler& handler;
        Event event;
    };
    explicit LinuxEpoll(LogAdapter&);
    void add(Handler&, Event);
    void del(Handler&);
    void process(int);

private:
    int epollFd_{0};
    std::unordered_map<int, HandlerContext> handlers_{};
    std::unique_ptr<struct ::epoll_event[]> events_{nullptr};
    size_t eventsSize_{0};
    LogAdapter& log_;
};
} // namespace fdxx
