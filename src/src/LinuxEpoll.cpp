
#include "LinuxEpoll.hpp"

#include <iostream>
#include "fdxx/Handler.hpp"

using fdxx::LinuxEpoll;

LinuxEpoll::LinuxEpoll()
{
    epollFd_ = ::epoll_create1(0);
}

inline void epollCtlWithCheck(int epfd, int op, int fd, struct epoll_event *event)
{
    auto res = ::epoll_ctl(epfd, op, fd, event);
    if (res < 0)
    {
        auto errorNum = errno;
        std::string error = "epoll_ctl failed, error: " + std::to_string(errno);
        throw std::runtime_error(error);
    }
}

void LinuxEpoll::add(std::shared_ptr<Handler> handler, const Event event) {
    struct ::epoll_event ev;
    auto fd = handler->fd();
     ev.events = EPOLLET;
    ev.data.fd = fd;
    if ((event & Event::read) != Event::none) {
        ev.events |= EPOLLIN | EPOLLPRI;
    }
    if ((event & Event::write) != Event::none) {
        ev.events |= EPOLLOUT;
    }
    if ((event & Event::error) != Event::none) {
        ev.events |= EPOLLERR| EPOLLHUP| EPOLLRDHUP;
    }
    epollCtlWithCheck(epollFd_, EPOLL_CTL_ADD, fd, &ev);
    handlers_.emplace(fd, HandlerContext{handler, event});
}

void LinuxEpoll::del(std::shared_ptr<Handler> handler)
{
    auto fd = handler->fd();
    epollCtlWithCheck(epollFd_, EPOLL_CTL_DEL, fd, nullptr);
    handlers_.erase(fd);
}

void LinuxEpoll::process(const int milliseconds)
{
    if (eventsSize_ < handlers_.size())
    {
        events_ = std::make_unique<struct ::epoll_event[]>(handlers_.size());
    }
    auto num = ::epoll_wait(epollFd_, events_.get(), handlers_.size(), milliseconds);
    std::cout << num << " " << handlers_.size() << std::endl;
    for(int i=0; i< num; ++i) {
        auto fd = events_[0].data.fd;
        auto events = events_[0].events;
        auto &handlerContext = handlers_.at(fd);
        if ((events & (EPOLLIN | EPOLLPRI) != 0) && ((handlerContext.event & Event::read) != Event::none))
        {
            handlerContext.handler->handle(Event::read);
        }
        
    }
}
