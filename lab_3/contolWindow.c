#include "headersAndVariables.c"


const char progName[] = "Lab 3 Vlasiuk";

void initX() {
    unsigned long black, white;

    dis = XOpenDisplay((char *) 0);
    screen = DefaultScreen(dis);

    black = BlackPixel(dis, screen);
    white = WhitePixel(dis, screen);

    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, WIN_WIDTH, WIN_HEIGHT, 1, black, white);
    XSetStandardProperties(dis, win, progName, progName, None, NULL, 0, NULL);
    XSelectInput(dis, win, ExposureMask | KeyPressMask);

    gc = XCreateGC(dis, win, 0, 0);
    XMapRaised(dis, win);
}

void closeX() {
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

void redraw() {
    XClearWindow(dis, win);
}
