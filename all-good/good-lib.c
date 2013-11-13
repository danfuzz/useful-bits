/*
 * Copyright 2013 the DL Example Authors (Dan Bornstein et alia).
 * Licensed AS IS and WITHOUT WARRANTY under the Apache License,
 * Version 2.0. Details: <http://www.apache.org/licenses/LICENSE-2.0>
 */

void hook(const char *);

static void init(void) __attribute__((constructor));
static void init(void) {
    hook("init() called inside all-good.");
}

static void shutdown(void) __attribute__((destructor));
static void shutdown(void) {
    hook("shutdown() called inside all-good.");
}

void run(void) {
    hook("run() called inside all-good.");
}
