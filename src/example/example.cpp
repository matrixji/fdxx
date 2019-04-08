#include "fdxx/Fdxx.hpp"
#include <chrono>
#include <thread>

int main(int agrc, char *argv[]) {
  fdxx::RunloopFactory runloopFactory;
  auto loop = runloopFactory.create("example");
  loop->start();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  loop->stop();
  return 0;
}
