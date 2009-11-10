
#include <stdio.h>

#include "epsilon.h"
#include "epsilon/wm/wm.h"
#include "epsilon/event/event.h"
#include "epsilon/input/input.h"

void waitForKill(eps_Window* window) {
}

int main() {
    eps_Window* myWindow;
    int kill = 0;

    eps_wm_initialize();
    myWindow = eps_wm_createWindow(640, 480, 0);

    printf("getEvent test...");
    while (!kill) {

        eps_Event event;
        if (eps_event_getEvent(myWindow, &event)) {
            switch (event.type) {
            case EPS_EVENT_CLOSE:
                kill = 1;
                printf("Close event!  Huzzah.\n");
                break;
            default: break;
            }
        }

    }

    printf("waitEvent test...");
    kill = 0;
    while (!kill) {

        eps_Event event;
        if (eps_event_waitEvent(myWindow, &event)) {
            switch (event.type) {
            case EPS_EVENT_CLOSE:
                kill = 1;
                printf("Close event!  Commiting suicide.\n");
                break;
            default: break;
            }
        }

    }

    printf("Running sendEvent test.  If the window does not close by itself this time, the test failed.\n");
    printf("sendEvent test...");
    kill = 0;
    while (!kill) {

        eps_Event event;
        if (eps_event_getEvent(myWindow, &event)) {
            switch (event.type) {
            case EPS_EVENT_CLOSE:
                kill = 1;
                printf("Close event.\n");
                break;
            default: break;
            }
        }

        {
            eps_Event closeEvent;
            closeEvent.type = EPS_EVENT_CLOSE;
            eps_event_sendEvent(myWindow, &closeEvent);
        }
    }

    eps_wm_destroyWindow(myWindow);
    eps_wm_shutDown();
}
