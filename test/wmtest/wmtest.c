
#include <stdio.h>

#include "epsilon.h"
#include "epsilon/wm/wm.h"
#include "epsilon/event/event.h"

int main() {
    eps_Window* myWindow;
    int kill = 0;

    eps_wm_initialize();
    myWindow = eps_wm_createWindow(640, 480, 0);
    while (!kill) {

        eps_Event event;
        if (eps_event_waitEvent(myWindow, &event)) {
            switch (event.type) {
            case EPS_EVENT_CLOSE:
                kill = 1;
                printf("Close event!  Commiting suicide.\n");
                break;

            case EPS_EVENT_KEY:
                printf("Key event!  Key %i %s!\n",
                    event.key.keyCode, event.key.pressed ? "pressed" : "unpressed"
                );
                break;

            case EPS_EVENT_MOUSE_BUTTON_DOWN:
            case EPS_EVENT_MOUSE_BUTTON_UP:
                printf("Mouse button %i %s!\n",
                    event.mouse.buttonIndex, (event.type == EPS_EVENT_MOUSE_BUTTON_DOWN) ? "pressed" : "unpressed"
                );
                break;
            case EPS_EVENT_MOUSE_MOTION:
                printf("Mouse moved to %3i,%3i\n", event.mouse.x, event.mouse.y);
                break;
            case EPS_EVENT_MOUSE_WHEEL:
                printf("Mouse wheel moved to %i\n", event.mouse.wheelState);
                break;
            default:
                printf("Some other event I do not understand!!  Type is %i\n", event.type);
            }
        }
    }

    eps_wm_destroyWindow(myWindow);
    eps_wm_shutDown();
}
