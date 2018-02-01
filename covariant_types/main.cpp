#include <string>
#include <iostream>
#include <typeinfo>

#if __cplusplus < 201103L
#define nullptr NULL
#endif

class A
{
  public:
    virtual A* parent() const { return nullptr; }
    virtual ~A() {}
};

class B : public A
{
  public:
    B(A* a) : m_parent(a) {}
    A* parent() const { return m_parent; }
  private:
    A* m_parent;
};

class C : public B
{
  public:
    C(B* a) : B(a), m_parent(a) {}
    B* parent() const { return m_parent; }
  private:
    B* m_parent;
};

class D : public A
{
  public:
    D(B* a) : m_parent(a) {}
    B* parent() const { return m_parent; }
  private:
    B* m_parent;
};

class E : public A
{
  public:
    E(D* a) : m_parent(a) {}
    D* parent() const { return m_parent; }
  private:
    D* m_parent;
};

void print(const A* pa)
{
  std::cout
    << "ptr = " << pa
    << ", type = " << (pa ? typeid(*pa).name() : "nullptr")
    << std::endl;
}

int main()
{
  A a;
  B b(&a);
  C c(&b);
  D d(&b);
  E e(&d);
  A* p_other_c = &c;
  A* pa = a.parent();
  A* pb = b.parent();
  B* pc = c.parent();
  A* pc_other = p_other_c->parent(); // cannot get B*
  //C* pwrong = c.parent(); // error
  B* pd = d.parent(); // more specialized interface
  A* pd_base = d.parent(); // only base interface
  D* pe = e.parent();
  A* pe_base = e.parent();

             // here actual type of object
  print(pa); // NULL
  print(pb); // A
  print(pc); // B
  print(pc_other); // B
  print(pd);      // B
  print(pd_base); // B
  print(pe);      // D
  print(pe_base); // D
}
