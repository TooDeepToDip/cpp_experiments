#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#include <string>
#include <list>
#include <sstream>
#include <cstdarg>

namespace string
{
    /// trim from start
    std::string &ltrim(std::string &s);
    /// trim from end
    std::string &rtrim(std::string &s);
    /// trim from both ends
    std::string &trim(std::string &s);

    typedef std::list<std::string> stringlist;

    stringlist split(const std::string& s, const std::string& delimiter);
    std::string join(const stringlist& list, const std::string& delimiter);

    template <typename T,
              template<typename=T, typename=std::allocator<T> > class C>
    std::string join2(const C<T> &objs, const std::string &delimeter)
    {
        std::stringstream ss;
        std::string delim = "";
        for (typename C<T>::const_iterator it = objs.begin(), end = objs.end(); it != end; ++it)
        {
            ss << delim << *it;
            delim = delimeter;
        }
        return ss.str();
    }

    bool contains(const std::string& origin, const std::string& substr);

    template<typename T>
    std::string from(const T& t)
    {
        std::stringstream s;
        s << t;
        return s.str();
    }

    std::string to_upper(const std::string &value);

    std::string replace(const std::string& origin, const std::string& oldStr, const std::string& newStr, int count = 0);
}

#endif /* STRING_HELPERS_H */
