/*
 * Copyright 2013 the DL Example Authors (Dan Bornstein et alia).
 * Licensed AS IS and WITHOUT WARRANTY under the Apache License,
 * Version 2.0. Details: <http://www.apache.org/licenses/LICENSE-2.0>
 */

void hook(const char *);
void notFound(void);

static void init(void) __attribute__((constructor));
static void init(void) {
    hook("init() called inside missing-import.");
}

void run(void) {
    hook("run() called inside missing-import.");
    notFound();
}
