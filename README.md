Dynamic Library Loading Example
===============================

This is a small example which shows:

* How to build a dynamic library with intentional holes.
* How to load and use such a library within a host runtime.

This is the sort of thing that needs to be done in a general
language runtime that supports runtime loading of additional
libraries.

In this case, the `host` executable exports a function named
`hook`, and it expects each library to export a function called
`run`. You run `host` passing it the file names of one or more
libraries. It opens each library, looks up the `run` function,
and calls it.

The code has been tested on OS X (compiled with Clang) and
Linux (compiled with Gcc, and running in a Gnu environment).

Subdirectories of this project
------------------------------

* etc &mdash; Miscellaneous support files

* host &mdash; The `host` executable

* blort &mdash; Library example. It is a proper library, importing `hook`,
  exporting `run`, and defining library constructor and destructor functions.

* frotz &mdash; Library example. It is a proper library despite the fact
  that it attempts to export the symbol `notFound`, which is not exported
  by the host. It succeeds, because it declares the symbol reference as
  "weak", which means that it gets set to `NULL` when the library is loaded.

* missing-export &mdash; Library example. It should succeed in loading
  and initializing, but it shoudl fail to run, because it does not export
  the symbol `run`. The host always tries to look that symbol up.

* missing-import &mdash; Library example. It should fail to load, because it
  attempts to import the symbol `notFound`, which is not exported by the
  host.

Testing
-------

To test the code, run the `test` script in the base directory of
the project. You should see something like this:

```
$ ./test
Building: host
Building: all-good
Building: missing-import
Building: missing-export
Building: weak-import
Done!

./all-good/all-good.lib: Loading
>>> init() called inside all-good.
./all-good/all-good.lib: Running
>>> run() called inside all-good.
./all-good/all-good.lib: Closing
>>> shutdown() called inside all-good.
./all-good/all-good.lib: Done.

./missing-export/missing-export.lib: Loading
>>> init() called inside missing-export.
./missing-export/missing-export.lib: Running
Trouble looking up `run`: dlsym(0x7fe2c9c03940, run): symbol not found
./missing-export/missing-export.lib: Closing
>>> shutdown() called inside missing-export.
./missing-export/missing-export.lib: Done.

./missing-import/missing-import.lib: Loading
./missing-import/missing-import.lib: Trouble loading: dlopen(./missing-import/missing-import.lib, 6): Symbol not found: _notFound
  Referenced from: ./missing-import/missing-import.lib
  Expected in: flat namespace
 in ./missing-import/missing-import.lib

./weak-import/weak-import.lib: Loading
>>> init() called inside weak-import.
./weak-import/weak-import.lib: Running
>>> run() called inside weak-import.
>>> Properly found that `notFound == NULL`.
./weak-import/weak-import.lib: Closing
>>> shutdown() called inside weak-import.
./weak-import/weak-import.lib: Done.
```

Contributing
------------

Contributions welcome! See the [guidelines](CONTRIBUTING.md).
