#include "autoTimer.h"
#include "arnlog.h"

#include "fmt/format.h"

AutoTimer::AutoTimer(const char* func, int line, const char* file) : m_startTime(std::chrono::steady_clock::now())
{
    m_fmtString = fmt::format("{}, line {}, {}", func, line, file);
}

AutoTimer::~AutoTimer() noexcept
{
    logInfo((m_fmtString + " {} seconds.").c_str(), std::chrono::duration<double>(std::chrono::steady_clock::now() - m_startTime).count());
}
