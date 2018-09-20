#include <iostream>
#include <list>
#include <algorithm>
#include "../helpers/container_helpers/predicates.hpp"

struct A
{
  A(int i)
    : i(i)
    , n(i + 5)
  {}
  int getI() const { return i; }
  //int getI() { return i; } // cannot specify overloading on call getter()
  // you can specify overloading with:
  // static getter<A, int () const>
  int i;
  int n;
};

std::ostream& operator<<(std::ostream& out, const A& a)
{
  return out << "{ i = " << a.i << ", n = "<< a.n << " }" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const A* a)
{
  return out << "{ i = " << a->i << ", n = "<< a->n << " }" << std::endl;
}

template <typename Container, typename Predicate>
void print_if(const Container& c, const Predicate& p)
{
  typedef typename Container::const_iterator ci;
  ci it = std::find_if(c.begin(), c.end(), p);
  if(it == c.end())
    std::cout << "not found" << std::endl;
  else
    std::cout << "found: " << *it << std::endl;
}

int main()
{
  std::list<A> list_a;
  std::list<A*> list_pa;
  std::list<const A*> list_cpa;
  for(size_t i = 0; i < 4; ++i)
  {
    list_a.push_back(A(i));
    list_pa.push_back(new A(i));
    list_cpa.push_back(new A(i));
  }
  using helpers::getter;
  print_if(list_a, getter(&A::getI, 2));
  print_if(list_pa, getter(&A::getI, 1));
  print_if(list_cpa, getter(&A::getI, 0));
  // why list_cpa doesn't call bool operator()(const T2* oth)?
  print_if(list_cpa, getter(&A::getI, 4));
}
