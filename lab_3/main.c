#include "contolWindow.c"
#include "matrix.c"
#include "graph.c"
#include "headersAndVariables.c"

int main() {
    XEvent event;
    KeySym key;
    char text[255];

    node *positions = getVerticesPositions();

    double **matrix = randm(10);
    double **adjacencyMatrix = mulmr(K, matrix);
    printf("Adjacency matrix:\n");
    printMatrix(adjacencyMatrix);

    double **symmetricMatrix = symmetrizeMatrix(adjacencyMatrix);
    printf("Symmetric matrix:\n");
    printMatrix(symmetricMatrix);



    initX();

    while (1) {
        XNextEvent(dis, &event);

        if (event.type == Expose && event.xexpose.count == 0) {
            redraw();
        }
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q') {
                freeMatrix(adjacencyMatrix);
                freeMatrix(symmetricMatrix);
                free(positions);
                closeX();
            } else if (text[0] == '1'){
                redraw();
                connectVerticesDirected(adjacencyMatrix, positions);
                draw_nodes();
            } else if (text[0] == '2') {
                redraw();
                connectVerticesUndirected(symmetricMatrix, positions);
                draw_nodes();
            }
        }
    }
}
