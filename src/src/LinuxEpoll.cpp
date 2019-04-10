#include "LinuxEpoll.hpp"
#include <functional>
#include "fdxx/Fdxx.hpp"

using fdxx::LinuxEpoll;

int syscallWithCheck(const std::function<int(void)>& func)
{
    auto res = func();
    if (res < 0)
    {
        auto err = errno;
        std::string error = "epoll_ctl failed, error: " + std::to_string(err);
        throw std::runtime_error(error);
    }
    return res;
}

LinuxEpoll::LinuxEpoll(LogAdapter& logAdapter) : log_(logAdapter)
{
    epollFd_ = syscallWithCheck([this]() { return ::epoll_create1(0); });
}

void LinuxEpoll::add(Handler& handler, const Event event)
{
    ::epoll_event ev{0};
    auto fd = handler.fd();
    ev.events = EPOLLET;
    ev.data.fd = fd;
    if ((event & Event::read) != Event::none)
    {
        ev.events |= EPOLLIN | EPOLLPRI;
    }
    if ((event & Event::write) != Event::none)
    {
        ev.events |= EPOLLOUT;
    }
    if ((event & Event::error) != Event::none)
    {
        ev.events |= EPOLLERR | EPOLLHUP | EPOLLRDHUP;
    }
    syscallWithCheck([this, &fd, &ev]() { return ::epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &ev); });
    handlers_.emplace(fd, HandlerContext{handler, event});
}

void LinuxEpoll::del(Handler& handler)
{
    auto fd = handler.fd();
    syscallWithCheck([this, &fd]() { return ::epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, nullptr); });
    handlers_.erase(fd);
}

void LinuxEpoll::process(const int milliseconds)
{
    if (eventsSize_ < handlers_.size())
    {
        events_ = std::make_unique<struct ::epoll_event[]>(handlers_.size());
    }
    auto num = ::epoll_wait(epollFd_, events_.get(), static_cast<int>(handlers_.size()), milliseconds);
    for (int i = 0; i < num; ++i)
    {
        auto fd = events_[i].data.fd;
        auto events = events_[i].events;
        auto& context = handlers_.at(fd);
        if (((events & (EPOLLIN | EPOLLPRI)) != 0) && ((context.event & Event::read) != Event::none))
        {
            context.handler.handle(Event::read);
        }
        if (((events & EPOLLOUT) != 0) && ((context.event & Event::write) != Event::none))
        {
            context.handler.handle(Event::write);
        }
        if (((events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) != 0) && ((context.event & Event::error) != Event::none))
        {
            context.handler.handle(Event::error);
        }
    }
}
