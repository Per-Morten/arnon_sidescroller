/// ArnonSidescroller

/* 
 * Arnlog contains a simple interface around a 
 * default logger object that is simple and quick
 * to utilize.
 */

#ifndef ARNLOG_H
#define ARNLOG_H

#include "logger.h"

#include <utility>

extern Logger g_log;

namespace detail
{
 /*!
 * \brief Uses a default logger object to quickly log a message
 * \param formatString - The log message with optional formatting
 * \param level - The log level to log at
 * \param args - The optional format arguments required to format the provided string
 */
template<typename... ArgList>
void log(const char* formatString, ELogLevel level, ArgList&&... args)
{
#ifndef NDEBUG
    g_log.log(formatString, level, std::forward<ArgList>(args)...);
#endif
}
}

/*!
 * \brief Uses a default logger object to quickly log a debug message
 */
template<typename... ArgList>
void logDebug(const char* formatString, ArgList&&... args)
{
    detail::log(formatString, ELogLevel::Debug, std::forward<ArgList>(args)...);
}

/*!
* \brief Uses a default logger object to quickly log an info message
*/
template<typename... ArgList>
void logInfo(const char* formatString, ArgList&&... args)
{
    detail::log(formatString, ELogLevel::Info, std::forward<ArgList>(args)...);
}

/*!
* \brief Uses a default logger object to quickly log a warning message
*/
template<typename... ArgList>
void logWarn(const char* formatString, ArgList&&... args)
{
    detail::log(formatString, ELogLevel::Warn, std::forward<ArgList>(args)...);
}

/*!
* \brief Uses a default logger object to quickly log an error message
*/
template<typename... ArgList>
void logErr(const char* formatString, ArgList&&... args)
{
    detail::log(formatString, ELogLevel::Error, std::forward<ArgList>(args)...);
}

#endif // ARNLOG_H
