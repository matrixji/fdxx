#include "fdxx/DefaultLogger.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

using fdxx::DefaultLogAdapter;
using fdxx::LogLevel;

namespace
{
std::string getTime()
{
    const auto now = std::chrono::system_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    const auto timer = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&timer), "%T");
    oss << ':' << std::setfill('0') << std::setw(3) << milliseconds.count();
    return oss.str();
}

std::string getLevel(const LogLevel level)
{
    std::string ret{"NONE"};
    switch (level)
    {
        case LogLevel::info:
            ret = "INFO";
            break;
        case LogLevel::warn:
            ret = "WARN";
            break;
        case LogLevel::error:
            ret = "ERROR";
            break;
        case LogLevel::critical:
            ret = "CRITICAL";
            break;
        case LogLevel::debug:
            ret = "DEBUG";
            break;
    }
    return ret;
}
} // namespace

void DefaultLogAdapter::log(const LogLevel level, const std::string& message, const std::string& file, int line)
{
    std::cout << getTime() << " [" << getLevel(level) << "] [" << file << ":" << line << "] " << message << std::endl;
}