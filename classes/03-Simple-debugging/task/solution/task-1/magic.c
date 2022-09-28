#include "magic.h"

#include <stdlib.h>

int initMagic(int argc, char** argv, int* firstOp, int* secondOp, char* operation) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    *firstOp = atoi(argv[1]);
    *secondOp = atoi(argv[3]);
    *operation = *argv[2];
    return EXIT_SUCCESS;
}