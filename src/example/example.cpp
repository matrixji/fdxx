#include "fdxx/Fdxx.hpp"
#include <sys/timerfd.h>
#include <chrono>
#include <iostream>
#include <thread>


struct Timer : public fdxx::Handler
{
    explicit Timer(int n) {
        struct timespec now;
        struct itimerspec newTm;
        clock_gettime(CLOCK_REALTIME, &now);
        newTm.it_value.tv_sec = now.tv_sec + n;
        newTm.it_value.tv_nsec = now.tv_nsec;
        fd_ = timerfd_create(CLOCK_REALTIME, 0);
        timerfd_settime(fd_, TFD_TIMER_ABSTIME, &newTm, nullptr);
    }
    virtual ~Timer() = default;
    int fd_{-1};
    int fd() override {
        return fd_;
    }
    void handle(const fdxx::Event &event) {
        std::cout << static_cast<unsigned>(event) << std::endl;
    }
};


int main(int agrc, char *argv[]) {
  fdxx::RunloopFactory runloopFactory;
  auto loop = runloopFactory.create("example");
  auto t1 = std::make_shared<Timer>(1);
  loop->regist(t1, fdxx::Event::all);
  loop->regist(std::make_shared<Timer>(2), fdxx::Event::all);
  loop->start();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  loop->stop();
  return 0;
}
