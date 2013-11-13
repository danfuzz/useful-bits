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

Subdirectories of this project
------------------------------

* etc &mdash; Miscellaneous support files

* host &mdash; The `host` executable

* blort &mdash; Library example. It is a proper library, importing `hook`,
  exporting `run`, and defining a library initialization function (called
  a "constructor").

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
