
#include <stdio.h>

#include "epsilon.h"
#include "epsilon/wm/wm.h"
#include "epsilon/opengl/opengl.h"
#include "epsilon/event/event.h"
#include "epsilon/error/error.h"

#include <GL/gl.h>
#include <GL/glu.h>

void dumpErrors() {
    eps_Error* err;

    printf("%i Epsilon errors:\n", eps_error_getErrorCount());

    while (err = eps_error_getError()) {
        printf("Error %i: %s\n", err->code, err->message);
        eps_error_destroyError(err);
    }

    printf("---\n");
}

void drawScene() {
    const float rquad = 15.0f;
    const float rtri = 23.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glRotatef(rtri, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -7.0f);

	glRotatef(rquad, 1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
}

int main() {
    eps_Window* window;
    eps_OpenGLContext* context;
    int kill = 0;

    const int xres = 640;
    const int yres = 480;
    const double aspectRatio = ((double) xres) / ((double) yres);

    eps_wm_initialize();

    context = eps_opengl_createOpenGLWindow(xres, yres, 0, EPS_OPENGL_PF_32BPP);
    if (!context) {
        dumpErrors();
        return 1;
    }
    window = eps_opengl_getContextWindow(context);
    eps_wm_setCaption(window, "OpenGL Test");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0);
    glClearColor(0.0, 0.0, 0.4, 0.0);

    while (!kill) {
        eps_Event event;

        drawScene();

        eps_opengl_swapBuffers(context);

        if (eps_error_getErrorCount()) {
            dumpErrors();
            break;
        }

        if (eps_event_getEvent(window, &event)) {
            switch (event.type) {
                case EPS_EVENT_CLOSE: {
                    kill = 1;
                    printf("Close event!  Commiting suicide.\n");
                    break;
                }

                case EPS_EVENT_KEY: {
                    printf("Key event!  Key %i %s!\n",
                        event.key.keyCode, event.key.pressed ? "pressed" : "unpressed"
                    );
                    break;
                }

                case EPS_EVENT_MOUSE_BUTTON_DOWN:
                case EPS_EVENT_MOUSE_BUTTON_UP: {
                    printf("Mouse button %i %s!\n",
                        event.mouse.buttonIndex, (event.type == EPS_EVENT_MOUSE_BUTTON_DOWN) ? "pressed" : "unpressed"
                    );
                    break;
                }

                case EPS_EVENT_MOUSE_MOTION:
                case EPS_EVENT_MOUSE_WHEEL: {
                    break;
                }

                default: {
                    printf("Unknown event %i\n", event.type);
                    break;
                }
            }
        }
    }

    eps_opengl_destroyOpenGLWindow(context);
    eps_wm_shutDown();
}
