#include <stdexcept>
#include <iostream>

struct C
{
  int a;
  int b;
};

struct B
{
  B(const C& c) : c(c)
  {
    std::cout << "you shall not pass" << std::endl;
    throw std::runtime_error("B::ctor runtime error");
  }
  ~B() { std::cout << "You never see this message" << std::endl; }
  const C& c;
};

struct A
{
  A(const C& other_c)
    try // WWWHHHAAAA?!
    : some_data(other_c)
    , c()
    , b()
  {
    c = new C();
    b = new B(other_c);
  }
  catch(std::exception& e)
  {
    std::cout << "release b(if constructed), c" << std::endl;
    delete b;
    delete c;
  }
  ~A() { std::cout << "You also never see this message" << std::endl; }
  C some_data;
  C* c;
  B* b;
};

int main()
{
  C c;
  try
  {
    A a(c);
  }
  catch(const std::exception& e)
  {
    std::cout << "error: " << e.what() << std::endl;
  }
}
