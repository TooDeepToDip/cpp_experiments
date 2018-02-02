# C++ language standard version

If your code depends on language standard version, you can use this approach to isolate unportable code:


  ``__cplusplus``


  This macro is defined when the C++ compiler is in use. You can use ``__cplusplus`` to test whether a header is compiled by a C compiler or a C++ compiler. This macro is similar to ``__STDC_VERSION__``, in that it expands to a version number. Depending on the language standard selected, the value of the macro is **199711L** for the 1998 C++ standard, **201103L** for the 2011 C++ standard, **201402L** for the 2014 C++ standard, **201703L** for the 2017 C++ standard, or an unspecified value strictly larger than **201703L** for the experimental languages enabled by ``-std=c++2a`` and ``-std=gnu++2a``.

Also see [gcc predefined macros](https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html).
