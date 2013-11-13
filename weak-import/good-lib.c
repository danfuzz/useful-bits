/*
 * Copyright 2013 the DL Example Authors (Dan Bornstein et alia).
 * Licensed AS IS and WITHOUT WARRANTY under the Apache License,
 * Version 2.0. Details: <http://www.apache.org/licenses/LICENSE-2.0>
 */

#include <stdlib.h>

void hook(const char *);

// The declaration of `__attribute((weak))` makes it be a non-error that
// this isn't found.
void notFound(void) __attribute__((weak));

static void init(void) __attribute__((constructor));
static void init(void) {
    hook("init() called inside weak-import.");
}

void run(void) {
    hook("run() called inside weak-import.");
    if (notFound == NULL) {
        hook("Properly found that `notFound == NULL`.");
    } else {
        hook("Unexpectedly found that `notFound != NULL`.");
    }
}
