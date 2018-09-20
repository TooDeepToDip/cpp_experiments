#ifndef CONTAINER_HELPERS_H
#define CONTAINER_HELPERS_H

#include <algorithm>
#include <map>
#include <list>

namespace helpers
{
    template<typename Container>
    void append(Container& dest, const Container& src)
    {
        dest.insert(dest.end(), src.begin(), src.end());
    }

    template<typename T>
    bool contains(const T& container, const typename T::value_type& item)
    {
        return std::find(container.begin(), container.end(), item) != container.end();
    }

    //TODO list values(map)
    //TODO list keys(map)
    //TODO has_key(map)
    //TODO has_value(map)

    /// Collect elements from obj via getter T1::*get() and size T1::*size()
    //  into T2 via push_back()
    // Typical using:
    // class A_Holder
    // {
    // public:
    //   size_t size() const;
    //   A* get_a() const;
    // };
    // ...
    // std::list<const A*> list_a;
    // collect(*a_holder, &A_Holder::get_a, &A_Holder::size, list_a);
    // //now list_a contains "copy" of holder but through std::container
    // T1 hasn't const qualifier because it allows to use collect to const referece,
    // but it allows also using collect() with temporary objects (#tag2)
    // (see distil_containers)
    template<typename T1, typename AccessF, typename SizeF, typename T2>
    T2& collect(T1& obj, AccessF T1::*get, SizeF T1::*size, T2& to)
    {
      for(size_t i = 0; i < (obj.*size)(); ++i)
        to.push_back((obj.*get)(i));
      return to;
    }

    /// Helper-function to automatic implicit conversion
    // Typical using:
    // class A {...};
    // class B : public A { ... };
    // std::list<B*> list_b;
    // // ... fill list_b
    // std::list<A*> list_a;
    // distil(list_b, list_a);
    // //now list_a contains pointers to instances of B
    template<typename T1, typename T2>
    T2& distil(const T1& from, T2& to)
    {
        std::copy(from.begin(), from.end(), std::back_inserter(to));
        return to;
    }
}

#endif /* CONTAINER_HELPERS_H */
