#include <list>
#include <vector>
#include <deque>
#include <set>
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

  template <typename T, size_t N>
    std::list<T>
    list(const T (&arr)[N])
    {
      return std::list<T>(begin(arr), end(arr));
    }

  template <typename T, size_t N>
    std::vector<T>
    vector(const T (&arr)[N])
    {
      return std::vector<T>(begin(arr), end(arr));
    }

  template <typename T, size_t N>
    std::deque<T>
    deque(const T (&arr)[N])
    {
      return std::deque<T>(begin(arr), end(arr));
    }

  template <typename T, size_t N>
    std::set<T>
    set(const T (&arr)[N])
    {
      return std::set<T>(begin(arr), end(arr));
    }
}
