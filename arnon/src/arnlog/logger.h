/// ArnonSidescroller

/*
 * The logger is a logger that wraps FMT
 * and produces colored output based on
 * the error level.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <iomanip>

#include "fmt/format.h"
#include "fmt/ostream.h"

// Used to indicate a log level
enum class ELogLevel : uint8_t
{
    Debug,
    Info,
    Warn,
    Error
};

class Logger
{
private:
    // Format of the logger  [H  [M [S [msg
    const std::string logFormat = "[{:^7}][{}]  {}\n";

    // Name of the logger
    std::string m_name;

    // All previous log messages (to flush to file)
    std::vector<std::string> m_logOfLogs;

public:
    Logger(std::string name) : m_name(std::move(name)) {};

    // Log the given formatted message at level.
    template<typename... ArgList>
    void log(const char* formatString, ELogLevel level, ArgList&&... args);

    // Shortcut to log at Debug level
    template<typename... ArgList>
    void debug(const char* formatString, ArgList&&... args);

    // Shortcut to log at Info level
    template<typename... ArgList>
    void info(const char* formatString, ArgList&&... args);

    // Shortcut to log at Warning level
    template<typename... ArgList>
    void warn(const char* formatString, ArgList&&... args);

    // Shortcut to log at Error level
    template<typename... ArgList>
    void err(const char* formatString, ArgList&&... args);
};

template<typename... ArgList>
void Logger::log(const char* formatString, ELogLevel level, ArgList&&... args)
{
    // Format the log message and get the current time
    auto printMsg = fmt::format(formatString, std::forward<ArgList>(args)...);
    auto time = std::time(nullptr);

    // Produce the final message
    auto finalMessage = fmt::format(logFormat.c_str(), "DEBUG",
                                    std::put_time(std::localtime(&time), "%T"),
                                    printMsg);

    // Log at appropriate level (Colors / Visibility)
    switch (level)
    {
    case ELogLevel::Debug:
        printf("%s", finalMessage.c_str());
        break;
    case ELogLevel::Info:
        printf("%s", finalMessage.c_str());
        break;
    case ELogLevel::Warn:
        printf("%s", finalMessage.c_str());
        break;
    case ELogLevel::Error:
        printf("%s", finalMessage.c_str());
        break;
    }

    // Add to log history
    m_logOfLogs.emplace_back(std::move(finalMessage));
}

template<typename... ArgList>
void debug(const char* formatString, ArgList&&... args)
{
    log(formatString, ELogLevel::Debug, std::forward<ArgList>(args)...);
}

template<typename... ArgList>
void info(const char* formatString, ArgList&&... args)
{
    log(formatString, ELogLevel::Info, std::forward<ArgList>(args)...);
}

template<typename... ArgList>
void warn(const char* formatString, ArgList&&... args)
{
    log(formatString, ELogLevel::Warn, std::forward<ArgList>(args)...);
}

template<typename... ArgList>
void err(const char* formatString, ArgList&&... args)
{
    log(formatString, ELogLevel::Error, std::forward<ArgList>(args)...);
}

#endif  // LOGGER_H
