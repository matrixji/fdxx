#pragma once
#include "Logger.hpp"

namespace fdxx
{
class DefaultLogAdapter : public LogAdapter
{
public:
    void log(LogLevel level, const std::string& message, const std::string& file, int line) final;
};
} // namespace fdxx
