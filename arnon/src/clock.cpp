#include "clock.h"

/////////////////////////////////////
// STOPWATCH

Stopwatch::Stopwatch() : m_startTime(std::chrono::steady_clock::now())
{
}

Stopwatch::TimeUnit Stopwatch::getElapsedTime() const
{
    return std::chrono::steady_clock::now() - m_startTime;
}

Stopwatch::TimeUnit Stopwatch::restart()
{
    auto time = getElapsedTime();
    m_startTime = std::chrono::steady_clock::now();
    return time;
}

/////////////////////////////////////
// COUNTDOWN TIMER

CountDownTimer::CountDownTimer(TimeUnit countDownTime) : m_timeLeft(countDownTime), m_originalTime(countDownTime)
{
}

void CountDownTimer::restart()
{
    m_timeLeft = m_originalTime;
    m_triggered = false;
}

void CountDownTimer::update(float dt)
{
    m_timeLeft -= TimeUnit{ dt };
    if (!m_triggered && m_timeLeft < TimeUnit{ 0.f })
    {
        m_triggered = true;
        onCompleted.emit();
    }
}
