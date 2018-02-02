# Demangled typename

If you want see human-readable class name (and don't use macro), you can use this class (see also typeid).
So, here you can demangle name like this:
```
_ZN10SomeClassA4func -> SomeClass::func
```

This approach is platform dependent, implementation defined, but works)
