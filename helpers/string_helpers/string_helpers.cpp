#include <ctype.h>
#include "string_helpers.h"
#include <sstream>
#include <limits>
#include <algorithm>
//#include <cstdio>

namespace string
{

    std::string &ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                    std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    std::string &rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                    std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

    std::string &trim(std::string &s)
    {
        return ltrim(rtrim(s));
    }

    namespace
    {
        void splitTo(stringlist& l, const std::string& s, const std::string& delimiter)
        {
            std::string::size_type i = s.find(delimiter);
            l.push_back(s.substr(0, i));
            if(std::string::npos != i)
              splitTo(l, s.substr(i + delimiter.size()), delimiter);
        }
    }

    stringlist split(const std::string& s, const std::string& delimiter)
    {
        stringlist list;
        splitTo(list, s, delimiter);
        return list;
    }

    bool contains(const std::string& origin, const std::string& substr)
    {
        return origin.find(substr) != std::string::npos;
    }

    std::string to_upper(const std::string &value)
    {
        std::string upped;
        std::transform(value.begin(), value.end(), std::back_inserter(upped), ::toupper);
        return upped;
    }

    std::string replace(const std::string& origin, const std::string& oldStr, const std::string& newStr, int /*count = 0*/)
    {
      if(origin.find(oldStr) != std::string::npos)
      {
        stringlist parts = split(origin, oldStr);
        return join(parts, newStr);
      }
      else return origin;
    }
}
