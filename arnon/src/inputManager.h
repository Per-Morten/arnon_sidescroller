/// ArnonSidescroller

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <array>
#include <cstdint>
#include <type_traits>

#include "glm/vec2.hpp"

class InputManager
{
public:
    InputManager() { m_InputMask.fill(0); }

    // Clear the pressed key input mask
    void clear() { m_PressedKeyMask.fill(0); }

    // Tell input manager that the wheel was scrolled with the given delta
    void scrollMouse(const float delta) { m_ScrollDelta = delta; }

    // Get the latest scroll delta on the Y axis
    float getScrollDelta() const { return m_ScrollDelta; }

    // Tell input manager that the cursor has moved
    void moveCursor(const glm::vec2& newPosition) { m_CursorPosition = newPosition; }

    // Get the latest polled cursor position
    const glm::vec2 getCursorPosition() const { return m_CursorPosition; }

    // Tell input manager that the given key / mouse button has been pressed
    void pressKey(unsigned key) { ++m_InputMask[key]; m_PressedKeyMask[key] = 1u; }

    // Tell input manager that the given key / mouse button has been released
    void releaseKey(unsigned key) { m_InputMask[key] = 0; m_PressedKeyMask[key] = 0; }

    // Check if all given keys are currently in a pressed state or repeating [live]
    // This supports keys such as Ctrl, Alt Shift and all Mouse buttons too
    template<typename... Keys>
    bool arePressed(Keys... keys) const { return (... && m_InputMask[keys]); }

    // Check if all given keys were pressed down this frame [event-based]
    // This supports keys such as Ctrl, Alt Shift and all Mouse buttons too
    template<typename... Keys>
    bool wasPressed(Keys... keys) const { return (... && (m_PressedKeyMask[keys] == 1)); }

private:
    // Input Mask for keyboard keys and mouse buttons [live]
    std::array<uint8_t, 512> m_InputMask;

    // Input Mask for keyboard keys and mouse buttons [event based]
    std::array<uint8_t, 512> m_PressedKeyMask;

    // The current position of the cursor
    glm::vec2 m_CursorPosition;

    // Stores the latest scroll delta
    float m_ScrollDelta;
};

#endif // INPUTMANAGER_H
