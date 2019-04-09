#include <chrono>
#include <iostream>
#include <thread>
#include "fdxx/Fdxx.hpp"

int main(int argc, char* argv[])
{
    fdxx::DefaultLogAdapter logAdapter;
    fdxx::RunloopFactory runloopFactory;
    fdxx::TimerFactory timerFactory;
    auto loop = runloopFactory.create("example", logAdapter);
    loop->add(
        timerFactory.create(
            500,
            500,
            logAdapter,
            [&logAdapter](fdxx::Handler& handler, bool hasTimeout) { LOG_INFO(logAdapter) << "x"; }),
        fdxx::Event::all);
    loop->add(
        timerFactory.create(
            1000,
            1000,
            logAdapter,
            [&logAdapter](fdxx::Handler& handler, bool hasTimeout) { LOG_INFO(logAdapter) << "y"; }),
        fdxx::Event::all);
    loop->start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    loop->stop();
    return 0;
}
