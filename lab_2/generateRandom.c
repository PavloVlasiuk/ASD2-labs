#include <time.h>


double generateRandom() {
    srand(clock());
    return (double) rand() / RAND_MAX * 10;
}
