#include <iostream>
#include <cstddef>

class A
{
public:
  A(int a = 0) : m_a(a) {}
  virtual ~A() {}
  virtual void foo() const
  {
    std::cout << "hello: " << m_a << std::endl;
  }
private:
  int m_a;
};

class B : virtual public A
{
public:
  B(int b = 10) : A(b) {}
};

class C : virtual public A
{
public:
  C(int c = 30) : A(c) {}
};

class D : public B, public C
{
public:
  D() {}
  D(int b) : B(b) {}
  D(int c, void*) : C(c) {}
  D(int b, int c) : B(b), C(c) {}
  D(int a, int b, int c) : A(a), B(b), C(c) {}
};

int main()
{
  D d;                  // using A()
  d.foo();
  D d1(1);              // using A()
  d1.foo();
  D d2(2, (void*)NULL); // using A()
  d2.foo();
  D d3(3, 4);           // using A()
  d3.foo();
  D d4(5, 6, 7);        // using A(a)
  d4.foo();
  // explicit call A(a) is needed
  // because using virtual inheritance
}
