/*
Q:
What need one to change class A to make code correct?
You can't change class B and main().

class A
{
};

//----------------------------------------
class B
{
  const A a;
};

int main()
{
  B b;
  b = B();
}

A:
*/
#include <iostream>

// only for clang
// because gcc has a bug: it ignores default assignment operator
// through latter wouldn't be deleted
class A
{
public:
  A() { }
  const A& operator=(const A& a) const
  {
    if(this != &a)
    {
      m_i = a.m_i;
    }
    return *this;
  }
  int i() const { return m_i; }
private:
  mutable int m_i;
};

class B
{
  const A a;
  public:
  void foo() const
  {
    std::cout << "a = " << a.i() <<  std::endl;
  }
};

int main()
{
  B b;
  b.foo();
  b = B();
  b.foo();
}
