#pragma once

namespace fdxx {
class Logger {
public:
  Logger() = delete;
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;
  virtual ~Logger() = default;
  virtual void info(const std::string &) = 0;
};
} // namespace fdxx
