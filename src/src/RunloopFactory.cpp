#include "fdxx/RunloopFactory.hpp"
#include "fdxx/Logger.hpp"
#include "DefaultRunloop.hpp"

using fdxx::DefaultRunloop;
using fdxx::Runloop;
using fdxx::RunloopFactory;

std::unique_ptr<Runloop> RunloopFactory::create(std::string name, LogAdapter& logAdapter)
{
    return std::make_unique<DefaultRunloop>(std::move(name), logAdapter);
}
