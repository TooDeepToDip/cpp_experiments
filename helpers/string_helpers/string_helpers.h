#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#include <string>
#include <list>
#include <iterator>
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

    template <typename Container>
    std::string join(const Container& c, const std::string& delimiter)
    {
        std::stringstream ss;
        typedef typename Container::const_iterator ci;
        ci beg = c.begin();
        if(beg != c.end())
        {
          ss << *beg;
          std::advance(beg, 1);
          for(ci it = beg, end = c.end(); it != end; ++it)
            ss << delimiter << *it;
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
