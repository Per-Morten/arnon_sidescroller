/// ArnonSidescroller

#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <utility> // forward
#include <iomanip> // put_time

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

/*!
 * \brief The Logger class handles logging at four different log
 * levels. Debug, Info, Warning and Error. It wraps FMT
 * and produces colored output based on the error level. Logs
 * can also be printed to a file.
 */
class Logger
{
private:
    // Format of the logger  [H  [M [S [msg
    const std::string logFormat = "[{:^7}][{}]  {}\n";

    // Name of the logger
    std::string m_name;

    // All previous log messages (to flush to file)
    std::vector<std::string> m_logOfLogs;

    // Will only log items at current or higher log levels
    ELogLevel m_logMask = ELogLevel::Debug;

public:
    Logger(std::string name) : m_name(std::move(name)) {};

    /*!
     * \brief log logs the given formatString at level
     * \param formatString - The log message with optional formatting
     * \param level - The log level to log at
     * \param args - The optional format arguments required to format the provided string
     */
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

    // Flush the log history to a log file
    inline void toFile(const std::string& filename) const;

    /*!
     * \brief setLogMask sets the log visibilty mask
     * \param maskLevel - The new level to mask at
     */
    inline void setLogMask(ELogLevel maskLevel);

private:
    /*!
     * \brief checkLogLevel checks the current log mask against the level of other
     * \param other - The log level to check against
     * \return true if other is the same or higher than the current mask
     */
    bool checkLogLevel(ELogLevel other) const;
};

template<typename... ArgList>
void Logger::log(const char* formatString, ELogLevel level, ArgList&&... args)
{
    // Format the log message and get the current time
    const auto printMsg = fmt::format(formatString, std::forward<ArgList>(args)...);
    const auto time = std::time(nullptr);

    // Produce the final message [ non const since it will be moved from later ]
    auto finalMessage = fmt::format(logFormat.c_str(), "LEVEL",
                                    std::put_time(std::localtime(&time), "%T"),
                                    printMsg);

    // Log at appropriate level (Colors / Visibility)
    // #TODO : Implement coloring (WIN32) and visibility
    // #NOTE : Linux can use ASCII escape sequence, Windows will have to be more tricksy...
    if(checkLogLevel(level))
    {
        switch (level)
        {
        case ELogLevel::Debug:
#ifdef __linux__
            printf("\33[37%s\33[0m", finalMessage.c_str());
#elif _WIN32
            // #TODO: Some mythical WinAPI Call noone ever heard about before /shrug
#endif
            break;
        case ELogLevel::Info:
#ifdef __linux__
            printf("\33[37m%s\33[0m", finalMessage.c_str());
#elif _WIN32

#endif
            break;
        case ELogLevel::Warn:
#ifdef __linux__
            printf("\33[33m%s\33[0m", finalMessage.c_str());
#elif _WIN32

#endif
            break;
        case ELogLevel::Error:
#ifdef __linux__
            printf("\33[31m%s\33[0m", finalMessage.c_str());
#elif _WIN32

#endif
            break;
        }
    }

    // Add to log history regardless of log level
    m_logOfLogs.emplace_back(std::move(finalMessage));
}

template<typename... ArgList>
void Logger::debug(const char* formatString, ArgList&&... args)
{
    log(formatString, ELogLevel::Debug, std::forward<ArgList>(args)...);
}

template<typename... ArgList>
void Logger::info(const char* formatString, ArgList&&... args)
{
    log(formatString, ELogLevel::Info, std::forward<ArgList>(args)...);
}

template<typename... ArgList>
void Logger::warn(const char* formatString, ArgList&&... args)
{
    log(formatString, ELogLevel::Warn, std::forward<ArgList>(args)...);
}

template<typename... ArgList>
void Logger::err(const char* formatString, ArgList&&... args)
{
    log(formatString, ELogLevel::Error, std::forward<ArgList>(args)...);
}

void Logger::toFile(const std::string& filename) const
{
    std::ofstream outFile(filename);
    for(const auto& line : m_logOfLogs)
    {
        outFile << line;
    }
}

bool Logger::checkLogLevel(ELogLevel other) const
{
    return static_cast<uint16_t>(other) >= static_cast<uint16_t>(m_logMask);
}

#endif  // LOGGER_H
