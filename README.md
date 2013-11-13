Dynamic Library Loading Example
-------------------------------

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
