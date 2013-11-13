/*
 * Copyright 2013 the DL Example Authors (Dan Bornstein et alia).
 * Licensed AS IS and WITHOUT WARRANTY under the Apache License,
 * Version 2.0. Details: <http://www.apache.org/licenses/LICENSE-2.0>
 */

void hook(const char *);

static void init(void) __attribute__((constructor));
static void init(void) {
    hook("init() called inside missing-export.");
}

// `run` is intentionally *not* defined in this code.
