#pragma once
#include "Logger.hpp"

namespace fdxx
{
class DefaultLogAdapter : public LogAdapter
{
public:
    void log(fdxx::LogLevel, const std::string&, const std::string&, int) final;
};
} // namespace fdxx
