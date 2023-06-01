#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>



Display *dis;
int screen;
Window win;
GC gc;



#define N 10
#define NODE_RADIUS 20
#define WIN_HEIGHT 700
#define WIN_WIDTH 1000

#define MARGIN_BOTTOM 100
#define MARGIN_TOP 200
#define MARGIN_LEFT 100
#define MARGIN_RIGHT 100

#define N1 2
#define N2 2
#define N3 0
#define N4 5
#define K (1.0 - N3 * 0.02 - N4 * 0.005 - 0.25)
