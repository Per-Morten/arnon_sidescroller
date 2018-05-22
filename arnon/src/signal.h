/// ArnonSidescroller

#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <type_traits>

template<typename SlotType>
class Signal
{
private:
    // Vector of all slots that subscribe to this signal
    std::vector<SlotType> m_subscribers;

public:
    // Clear all connected slots
    void clear()
    {
        m_subscribers.clear();
    }

    // Connect a new slot to the signal
    void connect(SlotType newSlotSubscriber)
    {
        m_subscribers.emplace_back(std::move(newSlotSubscriber));
    }

    // Emit the Signal with provided Args
    template<typename... Args>
    void emit(const Args&... args)
    {
        for (const auto& slot : m_subscribers) slot(args...);
    }
};


#endif // SIGNAL_H
