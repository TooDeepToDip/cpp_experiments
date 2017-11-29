#include <list>
#include <algorithm>

namespace array_helpers
{
  template <class T, size_t N>
    const T* begin(const T (&arr)[N])
    {
      return arr;
    }

  template <class T, size_t N>
    const T* end(const T (&arr)[N])
    {
      return arr + N;
    }

  template <class T, size_t N>
    T* begin(T (&arr)[N])
    {
      return arr;
    }

  template <class T, size_t N>
    T* end(T (&arr)[N])
    {
      return arr + N;
    }

  template <typename T, size_t N>
    bool contains(const T (&arr)[N], const T& value)
    {
      return std::find(begin(arr), end(arr), value) != end(arr);
    }
}
