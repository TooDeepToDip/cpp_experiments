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

void print(const std::list<A>& l)
{
  std::cout << '{';
  for(auto it = l.begin(), end = l.end(); it != end; ++it)
  {
    if(it != l.begin()) std::cout << ", ";
    std::cout << *it;
  }
  std::cout << '}' << std::endl;
}

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
  std::list<A> simple_list(h::begin(arr2), h::end(arr2)); // too simple!!!
  std::cout << "incorrect_list :" << std::endl;
  print(incorrect_list);
  std::cout << "correct_list :" << std::endl;
  print(correct_list);
  std::cout << "simple_list :" << std::endl;
  print(simple_list);
  std::cout << std::endl << "---arrays---" << std::endl;
  std::cout << "arr :" << std::endl;
  print(arr);
  std::cout << "arr2 :" << std::endl;
  print(arr2);
  // or since c++11
  //for(auto it = arr2, end = h::end(arr2); it != end; ++it)
  //{
  //  std::cout << *it << std::endl;
  //}
  std::cout << std::endl << "------------" << std::endl;
  std::cout << "in arr found 3? "
    << ((std::find(arr, h::end(arr), 3) != h::end(arr)) ?
        "true" : "false") << std::endl;
  std::cout << "in arr found 7? "
    << ((std::find(arr, h::end(arr), 7) != h::end(arr)) ?
        "true" : "false") << std::endl;
  A tmp = { 2, 'a' };
  A tmp2 = { 3, 'a' };
  std::cout << "in arr2 found " << tmp << "? "
    << ((std::find(arr2, h::end(arr2), tmp) != h::end(arr2)) ?
    "true" : "false") << std::endl;
  std::cout << "arr contains " << 3 << ": " << (h::contains(arr, 3) ? "true" : "false") << std::endl;
  std::cout << "arr contains " << 7 << ": " << (h::contains(arr, 7) ? "true" : "false") << std::endl;
  std::cout << "arr2 contains " << tmp << ": " << (h::contains(arr2, tmp) ? "true" : "false") << std::endl;
  std::cout << "arr2 contains " << tmp2 << ": " << (h::contains(arr2, tmp2) ? "true" : "false") << std::endl;
}
