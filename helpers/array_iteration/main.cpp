#include <iostream>
#include "array_iteration.h"
#include "struct_a.h"

  template <class T, size_t N>
void print(const T(& l)[N])
{
  std::cout << '{';
  namespace h = array_helpers;
  for(auto it = l, end = h::end(l); it != end; ++it)
  {
    if(it != h::begin(l)) std::cout << ", ";
    std::cout << *it;
  }
  std::cout << '}' << std::endl;
}

template<typename T>
void print(const T& t)
{
  std::cout << t << std::endl;
}

template<typename T, template <typename, typename = std::allocator<T> > class C>
void print(const C<T>& l)
{
  std::cout << '{';
  for(auto it = l.begin(), end = l.end(); it != end; ++it)
  {
    if(it != l.begin()) std::cout << ", ";
    std::cout << *it;
  }
  std::cout << '}' << std::endl;
}

template<typename T
  , template <typename, typename = std::less<T>, typename = std::allocator<T> > class C>
void print(const C<T>& l)
{
  std::cout << '{';
  for(auto it = l.begin(), end = l.end(); it != end; ++it)
  {
    if(it != l.begin()) std::cout << ", ";
    std::cout << *it;
  }
  std::cout << '}' << std::endl;
}

#define PRINT(x) \
  std::cout << #x" :" << std::endl; \
  print(x);

#define BOOL_TO_STRING(x) \
  ((x) ? "true" : "false")

#define BOOL_PRINT(x) \
  std::cout << #x" : " << BOOL_TO_STRING(x) << std::endl;

#define FIND_PRINT(arr, it) \
  std::cout << "found " << it << " in "#arr" ? " << \
  BOOL_TO_STRING(std::find(h::begin(arr), h::end(arr), it) != h::end(arr)) << std::endl;

int main()
{
  namespace h = array_helpers;
  int arr[] = { 1, 2, 3, 4, 5, 6 };
  std::cout << "---byte count---" << std::endl;
  std::cout << "sizeof arr = " << sizeof(arr) << std::endl;
  std::cout << "sizeof *arr = " << sizeof(*arr) << std::endl;
  std::cout << "wrong len = " << sizeof(arr) << std::endl;
  std::cout << "true len = " << sizeof(arr) / sizeof(*arr) << std::endl;
  std::cout << "---lists---" << std::endl;
  A arr2[] = { { 1, 'c' }, { 2, 'a' }, { 2, 'b' } };
  std::list<A> incorrect_list(arr2, arr2 + sizeof(arr2)); // incorrect!!!
  std::list<A> correct_list(arr2, arr2 + sizeof(arr2) / sizeof(*arr2));
  std::list<A> simple_list = h::list(arr2); // too simple!!!
  PRINT(incorrect_list);
  PRINT(correct_list);
  PRINT(simple_list);
  std::cout << std::endl << "---arrays---" << std::endl;
  PRINT(arr);
  PRINT(arr2);
  // or since c++11
  //for(auto it = arr2, end = h::end(arr2); it != end; ++it)
  //{
  //  std::cout << *it << std::endl;
  //}
  std::cout << std::endl << "------------" << std::endl;
  FIND_PRINT(arr, 3);
  FIND_PRINT(arr, 7);
  A tmp = { 2, 'a' };
  A tmp2 = { 3, 'a' };
  FIND_PRINT(arr2, tmp);
  FIND_PRINT(arr2, tmp2);
  BOOL_PRINT(h::contains(arr, 3));
  BOOL_PRINT(h::contains(arr, 7));
  BOOL_PRINT(h::contains(arr2, tmp));
  BOOL_PRINT(h::contains(arr2, tmp2));
  std::vector<A> vec = h::vector(arr2);
  PRINT(vec.at(2));
  std::deque<A> deq = h::deque(arr2);
  PRINT(deq.at(0));
  std::set<A> set = h::set(arr2);
  PRINT(set);
}
