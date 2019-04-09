#include <sys/timerfd.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "fdxx/Fdxx.hpp"

struct Timer : public fdxx::Handler
{
    Timer(int n, fdxx::LogAdapter& logAdapter) : log_{logAdapter}
    {
        timespec now{};
        itimerspec newTm{};
        clock_gettime(CLOCK_REALTIME, &now);
        newTm.it_value.tv_sec = now.tv_sec + n;
        newTm.it_value.tv_nsec = now.tv_nsec;
        fd_ = timerfd_create(CLOCK_REALTIME, 0);
        timerfd_settime(fd_, TFD_TIMER_ABSTIME, &newTm, nullptr);
    }

    int fd_{-1};

    fdxx::LogAdapter& log_;

    int fd() override { return fd_; }

    void handle(const fdxx::Event event) final { LOG_INFO(log_) << "timer timeout"; }
};

int main(int agrc, char* argv[])
{
    fdxx::DefaultLogAdapter logAdapter;
    fdxx::RunloopFactory runloopFactory;
    auto loop = runloopFactory.create("example", logAdapter);
    loop->add(std::make_shared<Timer>(1, logAdapter), fdxx::Event::all);
    loop->add(std::make_shared<Timer>(2, logAdapter), fdxx::Event::all);
    loop->start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    loop->stop();
    return 0;
}
