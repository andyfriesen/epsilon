
#pragma once

#include "epsilon/event/event.h"

namespace Epsilon {

    public __value enum EventType {
        User = 0x0000,

        WmMarker= 0x1000,
        Close,

        MouseMarker = 0x1100,
        MouseMotion,
        MouseButtonDown,
        MouseButtonUp,
        MouseWheel,

        KeyMarker = 0x1200,
        Key,

        Invalid = 0xF000,
    };

    public __gc struct Event {
        EventType type;

        bool KeyPressed;
        uint KeyCode;

        uint MouseX;
        uint MouseY;
        uint MouseButtonState;
        uint MouseWheelState;
        uint MouseButtonIndex;
    };

    /// These things should probably be moved into the Window class
    public __sealed __gc struct EventThings {
        /// <summary>Peek an event from the queue if there is one.
        /// Does not remove the message from the queue.
        /// Returns null if the event queue is empty.</summary>
        Event* PeekEvent();

        /// <summary>Get an event from the queue if there is one.
        /// Returns null if the event queue is empty.</summary>
        Event* GetEvent();

        /// <summary>Wait until the event queue is not empty,
        /// then return an event.</summary>
        Event* WaitEvent();

        /// <summary>Send an event to a window.</summary>
        void SendEvent(Event* event);
    };

}
