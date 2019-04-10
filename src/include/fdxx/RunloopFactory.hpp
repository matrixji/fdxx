#pragma once
#include <memory>

namespace fdxx
{
class Runloop;
class LogAdapter;

class RunloopFactory
{
public:
    std::unique_ptr<Runloop> create(std::string name, std::shared_ptr<LogAdapter> logAdapter);
};
} // namespace fdxx
