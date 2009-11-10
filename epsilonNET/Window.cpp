
#include "Window.h"
#include "epsilon/wm/wm.h"

using namespace System::Text;

using namespace Epsilon;

Window::Window(uint width, uint height) {
}

void Window::Dispose() {
    PrivateDispose();
    GC::SuppressFinalize(this);
}

void Window::Move(int x, int y, uint width, uint height) {
    CheckPulse();
}

IntPtr Window::get_HWnd() {
    CheckPulse();

    return eps_wm_getHWnd(my_window);
}

String* Window::get_Caption() {
    CheckPulse();

    const uint len = 256;
    unsigned char bytes __gc[] = new unsigned char __gc[len];

    unsigned char __pin* ptr = &bytes[0];

    eps_bool result = eps_wm_getCaption(my_window, (eps_char*)ptr, len);
    // check result...

    return Encoding::UTF8->GetString(bytes);
}

void Window::set_Caption(String* caption) {
    CheckPulse();

    int byteCount = Encoding::UTF8->GetByteCount(caption);
    unsigned char bytes __gc[] = new unsigned char __gc[byteCount + 1];

    int result = Encoding::UTF8->GetBytes(caption, 0, caption->Length, bytes, 0);
    // check result...

    unsigned char __pin* ptr = &bytes[0];
    eps_wm_setCaption(my_window, (eps_char*)ptr);
}

void Window::PollMessages() {
    CheckPulse();

    PollMessages(false);
}

void Window::PollMessages(bool block) {
    CheckPulse();
}

MouseState Window::get_MouseState() {
    CheckPulse();

    Epsilon::MouseState state;
    eps_wm_getMouseState(my_window, &state.x, &state.y, &state.buttonMask);

    return state;
}

void Window::CheckPulse() {
    if (!my_window) {
        throw new System::InvalidOperationException("Attempt to operate on a disposed window");
    }
}

void Window::PrivateDispose() {
    if (!my_window) {
        return;
    }

    System::Threading::Monitor::Enter(this);
    try {
        eps_wm_destroyWindow(my_window);
        my_window = 0;

    } __finally {
        System::Threading::Monitor::Exit(this);
    }
}
