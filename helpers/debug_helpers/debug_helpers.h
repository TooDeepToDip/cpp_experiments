#ifndef DEBUG_HELPERS_H
#define DEBUG_HELPERS_H

#include <iosfwd>
namespace std { template<typename T1, typename T2> struct pair; }

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p)
{
  return out << "{ " << p.first << " : " << p.second << " }";
}

namespace debug
{
    template<class MapType>
    void print_map(std::ostream& out, const MapType & m)
    {
        typedef typename MapType::const_iterator ci;
        for(ci it = m.begin(), end = m.end(); it != end; ++it)
        {
            out << *it << "\n";
        }
    }

    template<class ContainerType>
    void print_container(std::ostream& out, const ContainerType & m)
    {
        typedef typename ContainerType::const_iterator ci;
        for(ci it = m.begin(), end = m.end(); it != end; ++it)
        {
            out << *it << "\n";
        }
    }
}

#endif /* DEBUG_HELPERS_H */
