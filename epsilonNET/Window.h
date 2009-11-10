
#pragma once

#using <mscorlib.dll>

#include "types.h"

struct _eps_Window;

namespace Epsilon {

    using namespace System;

    public __value struct MouseState {
        int x;
        int y;
        uint buttonMask;
    };

    public __gc struct Window : IDisposable{
        static void Initialize();
        static void ShutDown();

        Window(uint width, uint height);
        __sealed void Dispose();

        void Move(int x, int y, uint width, uint height);
        __property IntPtr get_HWnd();

        __property String* get_Caption();
        __property void set_Caption(String* caption);

        void PollMessages();
        void PollMessages(bool block);

        __property MouseState get_MouseState();

    private:
        void CheckPulse();
        void PrivateDispose();

        _eps_Window* my_window;
    };

}
