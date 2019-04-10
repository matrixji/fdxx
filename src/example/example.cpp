#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "fdxx/Fdxx.hpp"

int main(int argc, char* argv[])
{
    fdxx::DefaultLogAdapter logAdapter;
    fdxx::RunloopFactory runloopFactory;
    fdxx::TimerFactory timerFactory;
    auto loop = runloopFactory.create("example", logAdapter);
    int count = 3;
    std::vector<std::unique_ptr<fdxx::Timer>> timers;
    for (int i = 0; i < count; i++)
    {
        auto timer = timerFactory.create(
            500 + (i * 500), 500, logAdapter, [&logAdapter, i](fdxx::Timer& timer, bool hasTimeout) {
                LOG_INFO(logAdapter) << "timer: " << i << " timeout.";
            });
        loop->add(*timer, fdxx::Event::all);
        timers.emplace_back(std::move(timer));
    }
    loop->start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    loop->stop();
    return 0;
}
