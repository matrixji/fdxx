#include "fdxx/DefaultLogger.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

using fdxx::DefaultLogAdapter;
using fdxx::LogLevel;

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
    switch (level)
    {
        case LogLevel::info:
            return "INFO";
        case LogLevel::warn:
            return "WARN";
        case LogLevel::error:
            return "ERROR";
        case LogLevel::critical:
            return "CRIT";
        case LogLevel::debug:
            return "DEBUG";
        default:
            return "";
    }
}

void DefaultLogAdapter::log(const LogLevel level, const std::string& message, const std::string& file, int line)
{
    std::cout << getTime() << " [" << getLevel(level) << "] [" << file << ":" << line << "] " << message << std::endl;
}