#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include "fdxx/Fdxx.hpp"

int main()
{
    auto logAdapter = std::make_shared<fdxx::DefaultLogAdapter>();
    fdxx::RunloopFactory runloopFactory;
    fdxx::TimerFactory timerFactory;
    auto loop = runloopFactory.create("example", logAdapter);
    int count = 3;
    for (int i = 0; i < count; i++)
    {
        constexpr int64_t timeSpan{500};
        auto timeout = timeSpan + (i * timeSpan);
        auto interval = timeSpan;
        auto timer = timerFactory.create(timeout, interval, logAdapter, [&logAdapter, i](bool hasExpire) {
            LOG_INFO(logAdapter) << "timer: " << i << " timeout.";
        });
        std::shared_ptr<fdxx::Handler> timerHandler = std::make_shared<fdxx::Handler>(std::move(timer));
        loop->add(timerHandler, fdxx::Event::all);
    }
    loop->start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    loop->stop();

    return 0;
}
