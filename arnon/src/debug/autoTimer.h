/// ArnonSidescroller
///
#ifndef AUTOTIMER_H
#define AUTOTIMER_H

#include <chrono>
#include <string>

/*!
 * \brief The AutoTimer class is a scoped timer that prints the lifetime
 * of it's existence upon it's destruction.
 */
class AutoTimer
{
private:
    // Start Time
    std::chrono::steady_clock::time_point m_startTime;

    std::string m_fmtString;

public:
    AutoTimer(const char* func, int line, const char* file);

    ~AutoTimer() noexcept;
};

// Define that should be used with the auto timer
#define AUTO_TIMER(timerName) AutoTimer (timerName)(__func__, __LINE__, __FILE__)

#endif // AUTOTIMER_H
