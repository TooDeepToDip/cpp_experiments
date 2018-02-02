#ifndef TYPE_HELPERS_H
#define TYPE_HELPERS_H

#include <string>
#include <cstdlib>
#include <cxxabi.h>

namespace type_helpers
{
    template<typename T>
    std::string type_name()
    {
        int status;
        std::string tname = typeid(T).name();
        char* demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
        if(status == 0)
        {
            tname = demangled_name;
            std::free(demangled_name);
        }
        return tname;
    }
}

#endif /* TYPE_HELPERS_H */
