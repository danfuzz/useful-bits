/*
 * Copyright 2013 the DL Example Authors (Dan Bornstein et alia).
 * Licensed AS IS and WITHOUT WARRANTY under the Apache License,
 * Version 2.0. Details: <http://www.apache.org/licenses/LICENSE-2.0>
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

/**
 * This is the type of `run` functions defined by our libraries.
 */
typedef void runFunction(void);

/**
 * This is the hook function that is made available to the dynamically
 * loaded libraries.
 */
void hook(const char *str) {
    printf(">>> %s\n", str);
}

/**
 * Runs the `run` function in the indicated library.
 */
static void callRun(void *libHandle) {
    // The circumlocution used to assign `runFn` is required, because
    // directly assigning a `void *` to a function pointer type is
    // an undefined operation in ISO C. Reference:
    //     <http://pubs.opengroup.org/onlinepubs/009695399/functions/dlsym.html>
    runFunction *runFn;
    *(void **)(&runFn) = dlsym(libHandle, "run");

    if (runFn == NULL) {
        printf("Trouble looking up `run`: %s\n", dlerror());
        return;
    }

    runFn();
}

/**
 * Loads and runs the named library.
 */
static void runLib(const char *fileName) {
    printf("%s: Loading\n", fileName);

    // RTLD_NOW: Perform all dynamic linking immediately, so if there are
    // undefined symbols, there will be an error here and now. That is, this
    // will cause a bad library to fail to load at all, rather than get
    // confused somewhere down the line.
    //
    // RTLD_LOCAL: Do not add symbols exported from this library to the
    // global symbol namespace. The only way to get at bindings is by using
    // the handle for this library.
    void *libHandle = dlopen(fileName, RTLD_NOW | RTLD_LOCAL);
    if (libHandle == NULL) {
        printf("%s: Trouble loading: %s\n\n", fileName, dlerror());
        return;
    }

    printf("%s: Running\n", fileName);
    callRun(libHandle);

    printf("%s: Closing\n", fileName);

    int result = dlclose(libHandle);
    if (result != 0) {
        printf("%s: Trouble closing: %s\n\n", fileName, dlerror());
    }

    printf("%s: Done.\n\n", fileName);
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
