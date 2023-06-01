#include <math.h>
#include "headersAndVariables.c"


typedef struct node {
    int x;
    int y;
} node;

const int nonStraightConnectable[N][N] = {
        {0, 0, 1, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
};

void arrow(float fi, int px, int py) {
    fi = 3.1416 * (180.0 - fi) / 180.0;
    int lx, ly, rx, ry;

    lx = px + 15 * cos(fi + 0.3);
    rx = px + 15 * cos(fi - 0.3);
    ly = py + 15 * sin(fi + 0.3);
    ry = py + 15 * sin(fi - 0.3);

    XDrawLine(dis, win, gc, lx, ly, px, py);
    XDrawLine(dis, win, gc, px, py, rx, ry);
}

node *getVerticesPositions() {
    int indentation = 200;
    int x = MARGIN_LEFT;
    int y = WIN_HEIGHT - MARGIN_BOTTOM;
    node *nodePositions = malloc(sizeof(node) * N);

    for (int i = 0; i < N; i++) {
        if (WIN_WIDTH - x > MARGIN_RIGHT && y == WIN_HEIGHT - MARGIN_BOTTOM) {
            node node;
            node.x = x;
            node.y = y;
            nodePositions[i] = node;
            x += indentation;
        } else if (y > MARGIN_TOP && x > WIN_WIDTH / 2) {
            node node;
            node.x = x;
            node.y = y;
            nodePositions[i] = node;
            x = x - (WIN_WIDTH - x);
            y = y - (WIN_HEIGHT - y);
        } else if (y < MARGIN_TOP) {
            x = WIN_WIDTH / 2;
            y = MARGIN_TOP;
            node node;
            node.x = x;
            node.y = y;
            nodePositions[i] = node;
        } else {
            x = x - (WIN_HEIGHT - x - MARGIN_LEFT);
            y = y + (y - MARGIN_BOTTOM);
            node node;
            node.x = x;
            node.y = y;
            nodePositions[i] = node;
        }
    }

    return nodePositions;
}

void draw_nodes() {
    unsigned long bluePen = 0x3200FF;
    unsigned long whitePen = 0xFFFFFF;

    node *positions = getVerticesPositions();

    // struct to draw two digits numbers
    XFontStruct *fontInfo;
    fontInfo = XLoadQueryFont(dis, "fixed");

    if (!fontInfo) {
        fprintf(stderr, "Error loading font\n");
        return;
    }
    XSetFont(dis, gc, fontInfo->fid);

    for (int i = 1; i <= N; i++) {
        node pos = positions[i - 1];

        XSetForeground(dis, gc, whitePen);
        XFillArc(dis, win, gc, pos.x - NODE_RADIUS, pos.y - NODE_RADIUS, 2 * NODE_RADIUS,
                 2 * NODE_RADIUS, 0, 360 * 64);

        XSetForeground(dis, gc, bluePen);
        XSetLineAttributes(dis, gc, 2, LineSolid, CapButt, JoinMiter);
        XDrawArc(dis, win, gc, pos.x - NODE_RADIUS, pos.y - NODE_RADIUS, 2 * NODE_RADIUS,
                 2 * NODE_RADIUS, 0, 360 * 64);

        char numberOfNode[3];
        sprintf(numberOfNode, "%d", i);
        if (i < 10) {
            XDrawString(dis, win, gc, pos.x, pos.y, numberOfNode, 1);
        } else {
            XDrawString(dis, win, gc, pos.x, pos.y, numberOfNode, 2);
        }
    }

    XFreeFont(dis, fontInfo);
}

void drawArcConnection(node start, node end, int numStart, int numEnd) {
    const int width = abs(end.x - start.x);
    const int height = abs(end.y - start.y);
    const int offset = width / 10 + 55;

    if (start.y == end.y) {
        if (numStart < numEnd) {
            XDrawArc(dis, win, gc, start.x, start.y - 2 * NODE_RADIUS - 10, width, offset, 0, -180 * 64);
        } else {
            XDrawArc(dis, win, gc, end.x, end.y - 2 * NODE_RADIUS - 10, width, offset, 0, -180 * 64);
        }
    } else if (start.x >= WIN_WIDTH / 2 && end.x >= WIN_HEIGHT / 2) {
        if (numStart > numEnd) {
            XDrawArc(dis, win, gc, start.x - 3 * NODE_RADIUS, start.y - 2 * NODE_RADIUS, width + 100, height + 100,
                     135 * 64, -180 * 64);
        } else {
            XDrawArc(dis, win, gc, end.x - 3 * NODE_RADIUS, end.y - 2 * NODE_RADIUS, width + 100, height + 100,
                     135 * 64, -180 * 64);
        }
    } else if (start.x <= WIN_WIDTH / 2 && end.x <= WIN_WIDTH / 2) {
        int angleX = width;
        int angleY = height;
        if (width >= 2 * MARGIN_TOP) {
            XDrawArc(dis, win, gc, angleX - 390, angleY - 300, width + 170, height + 200, 45 * 64, 180 * 64);
        } else if (numStart < numEnd) {
            XDrawArc(dis, win, gc, angleX - end.x / 2 - 45, angleY - end.y / 2 + 100, width + 120,
                     height + 120, 45 * 64, 180 * 64);
        } else {
            XDrawArc(dis, win, gc, angleY - start.y / 2 + 5, angleX - start.x / 2 + 50, width + 120,
                     height + 120, 45 * 64, 180 * 64);
        }
    }
}

void connectVerticesUndirected(double **matrix, node *positions) {
    XSetLineAttributes(dis, gc, 1, LineSolid, CapButt, JoinMiter);
    unsigned long blackPen = 0x00000;
    XSetForeground(dis, gc, blackPen);
    for (int i = 0; i < N; i++) {
        node pos = positions[i];
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                if (i == j) {
                    XDrawArc(dis, win, gc, pos.x - NODE_RADIUS, pos.y - NODE_RADIUS + 20, 2 * NODE_RADIUS + 13,
                             2 * NODE_RADIUS + 13, 0, 360 * 64);
                } else if (nonStraightConnectable[i][j]) {
                    drawArcConnection(positions[i], positions[j], i, j);
                } else {
                    XDrawLine(dis, win, gc, positions[i].x, positions[i].y, positions[j].x, positions[j].y);
                }
            }
        }
    }
}

void arrowTo(double fromX, double fromY, double toX, double toY) {
    double difX = toX - fromX;
    double difY = toY - fromY;
    double arctg = atan(fabs(difY) / fabs(difX)) * 180 / M_PI;
    double angle, oppositAngle;
    if (difX >= 0 && difY < 0) angle = arctg, oppositAngle = M_PI / 180 * (angle + 180);
    else if (difX < 0 && difY < 0) angle = 180 - arctg, oppositAngle = M_PI / 180 * (angle + 180);
    else if (difX < 0 && difY >= 0) angle = 180 + arctg, oppositAngle = M_PI / 180 * (angle - 180);
    else angle = 360 - arctg, oppositAngle = M_PI / 180 * (angle - 180);
    arrow(angle, toX + 16 * cos(oppositAngle), toY - 16 * sin(oppositAngle));
}

void drawDirectLine(node start, node end, int numStart, int numEnd) {
    if (start.y == end.y) {
        if (numEnd < 5) {
            if (numStart < numEnd) {
                XDrawLine(dis, win, gc, start.x, start.y, end.x, end.y);
                arrow(0, end.x - NODE_RADIUS, end.y);
            } else {
                XDrawLine(dis, win, gc, start.x, start.y + 10, end.x, end.y + 10);
                arrow(180, end.x + NODE_RADIUS, end.y + 10);
            }
        } else {
            if (numStart > numEnd) {
                XDrawLine(dis, win, gc, start.x, start.y, end.x, end.y);
                arrow(0, end.x - NODE_RADIUS, end.y);
            } else {
                XDrawLine(dis, win, gc, start.x, start.y + 10, end.x, end.y + 10);
                arrow(180, end.x + NODE_RADIUS, end.y + 10);
            }
        }
    } else {
        if (numStart < numEnd) {
            XDrawLine(dis, win, gc, start.x, start.y, end.x, end.y);
            arrowTo(start.x, start.y, end.x, end.y);
        } else {
            if (abs(end.x - start.x) >= 400 && end.y - start.y < 0) {
                XDrawLine(dis, win, gc, start.x + 10, start.y, end.x + 10, end.y);
                arrowTo(start.x, start.y, end.x, end.y + 7);
            } else if (abs(end.x - start.x) >= 400 && end.y - start.y == 300) {
                XDrawLine(dis, win, gc, start.x + 10, start.y, end.x + 10, end.y);
                arrowTo(start.x, start.y, end.x + 5, end.y + 4);
            } else if (abs(end.x - start.x) >= 400 && end.y - start.y > 0) {
                XDrawLine(dis, win, gc, start.x + 10, start.y, end.x + 10, end.y);
                arrowTo(start.x, start.y, end.x - 5, end.y - 3);
            } else if (abs(end.y - start.y) >= 300) {
                XDrawLine(dis, win, gc, start.x + 10, start.y, end.x + 10, end.y);
                arrowTo(start.x, start.y, end.x + 12, end.y - 3);
            } else if (end.y - start.y == 100) {
                XDrawLine(dis, win, gc, start.x + 10, start.y, end.x + 10, end.y);
                arrowTo(start.x, start.y, end.x + 14, end.y);
            } else if (end.y - start.y < 0){
                XDrawLine(dis, win, gc, start.x + 10, start.y, end.x + 10, end.y);
                arrowTo(start.x + 10, start.y, end.x + 6, end.y + 8);
            } else {
                XDrawLine(dis, win, gc, start.x + 10, start.y, end.x + 10, end.y);
                arrowTo(start.x, start.y, end.x + 5, end.y - 7);
            }
        }
    }
}

void selfDirectedConnection(node vertex) {
    float fi = 135;
    arrow(fi, vertex.x + NODE_RADIUS, vertex.y + 3);
}

void drawDirectArc(node start, node end, int numStart, int numEnd) {
    const int width = abs(end.x - start.x);
    const int height = abs(end.y - start.y);
    const int offset = width / 10 + 55;

    if (start.y == end.y) {
        if (numStart < numEnd) {
            XDrawArc(dis, win, gc, start.x, start.y - 2 * NODE_RADIUS - 10, width, offset, 0, -180 * 64);
            arrow(30, end.x - 15, end.y + 15);
        } else {
            XDrawArc(dis, win, gc, end.x, end.y - 2 * NODE_RADIUS - 10, width, offset, 0, -180 * 64);
            arrow(120, end.x + 5, end.y + 20);
        }
    } else if (start.x >= WIN_WIDTH / 2 && end.x >= WIN_HEIGHT / 2) {
        if (numStart > numEnd) {
            XDrawArc(dis, win, gc, start.x - 3 * NODE_RADIUS, start.y - 2 * NODE_RADIUS, width + 100, height + 100,
                     135 * 64, -180 * 64);
            arrow(10, end.x, end.y);
        } else {
            XDrawArc(dis, win, gc, end.x - 3 * NODE_RADIUS, end.y - 2 * NODE_RADIUS, width + 100, height + 100,
                     135 * 64, -180 * 64);
            arrow(-40, end.x - 15, end.y - 10);
        }
    } else if (start.x <= WIN_WIDTH / 2 && end.x <= WIN_WIDTH / 2) {
        int angleX = width;
        int angleY = height;
        if (width >= 2 * MARGIN_TOP) {
            XDrawArc(dis, win, gc, angleX - 390, angleY - 300, width + 170, height + 200, 45 * 64, 180 * 64);
            arrow(-50, end.x - 20, end.y - 5);
        } else if (numStart < numEnd) {
            XDrawArc(dis, win, gc, angleX - end.x / 2 - 55, angleY - end.y / 2 + 110, width + 120,
                     height + 120, 45 * 64, 180 * 64);
            arrow(-40, end.x - 15, end.y - 10);
        } else {
            XDrawArc(dis, win, gc, angleY - start.y / 2 + 5, angleX - start.x / 2 + 50, width + 120,
                     height + 120, 45 * 64, 180 * 64);
            arrow(-45, end.x - 15, end.y - 10);
        }
    }
}

void connectVerticesDirected(double **matrix, node *positions) {
    XSetLineAttributes(dis, gc, 1, LineSolid, CapButt, JoinMiter);
    unsigned long blackPen = 0x00000;
    XSetForeground(dis, gc, blackPen);
    for (int i = 0; i < N; i++) {
        node pos = positions[i];
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                if (i == j) {
                    XDrawArc(dis, win, gc, pos.x - NODE_RADIUS, pos.y - NODE_RADIUS + 20, 2 * NODE_RADIUS + 13,
                             2 * NODE_RADIUS + 13, 0, 360 * 64);
                    selfDirectedConnection(positions[i]);
                } else if (nonStraightConnectable[i][j]) {
                    drawDirectArc(positions[i], positions[j], i, j);
                } else {
                    drawDirectLine(positions[i], positions[j], i, j);
                }
            }
        }
    }
}


