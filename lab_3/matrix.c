#include "headersAndVariables.c"


const int SEED = 2205;


double **randm(int n) {
    srand(SEED);
    double **matrix = malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(double) * n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (double) rand() / RAND_MAX * 2;
        }
    }
    return matrix;
}

double **mulmr(int k, double **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = matrix[i][j] > 1 ? 1 : 0;
        }
    }
    return matrix;
}

double **symmetrizeMatrix(double **matrix) {
    double **symmetricMatrix = malloc(sizeof(double *) * N);
    for (int i = 0; i < N; i++) {
        symmetricMatrix[i] = malloc(sizeof(double) * N);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            symmetricMatrix[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (symmetricMatrix[i][j] == 1) symmetricMatrix[j][i] = 1;
        }
    }
    return symmetricMatrix;
}

void printMatrix(double **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.0lf  ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(double **matrix) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

