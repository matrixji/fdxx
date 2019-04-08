#pragma once
#include <memory>

namespace fdxx {
class Runloop;

class RunloopFactory {
public:
  std::unique_ptr<Runloop> create(std::string name);
};
} // namespace fdxx
