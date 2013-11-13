/*
 * Copyright 2013 the DL Example Authors (Dan Bornstein et alia).
 * Licensed AS IS and WITHOUT WARRANTY under the Apache License,
 * Version 2.0. Details: <http://www.apache.org/licenses/LICENSE-2.0>
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * This is the hook function that is made available to the dynamically
 * loaded libraries.
 */
void hook(const char *str) {
    printf("%s\n", str);
}

/**
 * Loads and runs the named library.
 */
static void runLib(const char *fileName) {
    fprintf(stderr, "Running %s...\n", fileName);
}

/**
 * Loads and runs each of the libraries named on the command-line.
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Too few arguments.\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        runLib(argv[i]);
    }
}
