#pragma once
#include <cstring>
#include <sstream>

namespace fdxx
{
enum class LogLevel : unsigned
{
    debug = 1,
    info = 2,
    warn = 3,
    error = 4,
    critical = 5,
};

class LogAdapter
{
public:
    LogAdapter() = default;
    LogAdapter(const LogAdapter&) = delete;
    LogAdapter& operator=(const LogAdapter&) = delete;
    virtual ~LogAdapter() = default;
    virtual void log(LogLevel level, const std::string& message, const std::string& file, int line) = 0;
};

template <typename LogAdapter, LogLevel level>
class Logger
{
public:
    explicit Logger(LogAdapter& logAdapter, const char* filename, int line)
        : logAdapter_(logAdapter), filename_{getBasename(filename)}, line_{line}
    {
    }

    ~Logger() { logAdapter_.log(level, message_.str(), filename_, line_); }

    template <typename Input>
    Logger& operator<<(const Input& inputMessage)
    {
        message_ << inputMessage;
        return *this;
    }

    Logger& operator<<(std::ostream& (*streamModifier)(std::ostream&))
    {
        streamModifier(message_);
        return *this;
    }

private:
    static std::string getBasename(const char* filename)
    {
        std::string basename;
        auto ch = ::strrchr(filename, '/');
        if (ch == nullptr)
        {
            ch = ::strrchr(filename, '\\');
        }
        if (ch != nullptr)
        {
            basename = ch + 1;
        }
        else
        {
            basename = filename;
        }
        return basename;
    }
    LogAdapter& logAdapter_;
    std::string filename_{};
    int line_;
    std::stringstream message_{};
};
} // namespace fdxx

#define LOG_DEBUG(adapter) fdxx::Logger<decltype(adapter), fdxx::LogLevel::debug>(adapter, __FILE__, __LINE__)
#define LOG_INFO(adapter) fdxx::Logger<decltype(adapter), fdxx::LogLevel::info>(adapter, __FILE__, __LINE__)
#define LOG_WARN(adapter) fdxx::Logger<decltype(adapter), fdxx::LogLevel::warn>(adapter, __FILE__, __LINE__)
#define LOG_ERROR(adapter) fdxx::Logger<decltype(adapter), fdxx::LogLevel::error>(adapter, __FILE__, __LINE__)
#define LOG_CRITICAL(adapter) fdxx::Logger<decltype(adapter), fdxx::LogLevel::critical>(adapter, __FILE__, __LINE__)
