/// ArnonSidescroller

#ifndef CLOCK_H
#define CLOCK_H

#include "signal.h"

#include <chrono>

/*!
 * \brief The stopwatch is a clock to measure time and is
 * primarily designed for measuring delta time between frames.
 */
class Stopwatch
{
public:
    using TimeUnit = std::chrono::duration<float>;
    using TimePoint = decltype(std::chrono::steady_clock::now());

private:
    TimePoint m_startTime;

public:
    Stopwatch();

    TimeUnit getElapsedTime() const;

    TimeUnit restart();

};

/*!
 * \brief The countdown timer is a clock to count down from a
 * given time unit. An event will be fired upon completion.
 */
class CountDownTimer
{
public:
    using TimeUnit = std::chrono::duration<float>;

private:

    // Time left in countdown sequence
    TimeUnit m_timeLeft{ 0.f };

    // Original time of countdown
    TimeUnit m_originalTime{ 0.f };

    // Has the event fired
    bool m_triggered = false;

public:
    // Construct timer
    CountDownTimer(TimeUnit countDownTime);

    // Signal that fires once the timer is completed
    Signal<void()> onCompleted;

    // Restart the timer
    void restart();
    
    // Update the countdown timer
    void update(float dt);

};

#endif // CLOCK_H
