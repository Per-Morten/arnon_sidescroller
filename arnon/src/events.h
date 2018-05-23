/// ArnonSidescroller

/*!
 * \brief Contains a lot of type aliases for
 * various signals and slots. The purpose is to
 * make it easier to use and see the various available
 * events.
 */

#ifndef EVENTS_H
#define EVENTS_H

#include "slot.h"
#include "signal.h"

#include "glm/vec2.hpp"

// Fired when a mouse button is clicked
// Contains which mouse button and the location of the click
using ClickSlot = Slot<void(int, const glm::vec2&)>;
using ClickEvent = Signal<ClickSlot>;

// Fired when a keyboard key is pressed
// The int is what key was pressed using GLFW_KEY_WHATEVER
using KeyPressSlot = Slot<void(int)>;
using KeyPressEvent = Signal<KeyPressSlot>;

// Fired when a keyboard key is pressed
// The int is what key was released using GLFW_KEY_WHATEVER
using KeyReleaseSlot = Slot<void(int)>;
using KeyReleaseEvent = Signal<KeyPressSlot>;

// Fired when the mouse wheel is scrolled
// The float represents the scroll delta on the Y axis
using ScrollSlot = Slot<void(float)>;
using ScrollEvent = Signal<Slot<ScrollSlot>>;

#endif // EVENTS_H
