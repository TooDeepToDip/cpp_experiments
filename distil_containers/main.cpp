#include <iostream>
#include <deque>
#include <list>
#include <vector>

template<class ContainerType>                                   
void print_container(std::ostream& out, const ContainerType & m)
{                                                               
    typedef typename ContainerType::const_iterator ci;          
    for(ci it = m.begin(), end = m.end(); it != end; ++it)      
    {                                                           
        out << *(*it) << "\n";                                     
    }                                                           
}                                                               

struct A
{
  static int m_init;
  A() : a(++m_init) {}
  int a;
};

int A::m_init = 2;

std::ostream& operator<<(std::ostream& out, const A& a)
{
  return out << "A = { " << a.a << " }";
}

struct B : public A
{
  B(int b) : b(b) {}
  int b;
};

std::ostream& operator<<(std::ostream& out, const B& b)
{
  return out << "B = { " << (const A&)b << ", " << b.b << " }";
}

template<typename T1, typename AccessF, typename SizeF, typename T2>
T2& collect(T1& obj, AccessF get, SizeF size, T2& to)
{
  for(size_t i = 0; i < (obj.*size)(); ++i)
    to.push_back((obj.*get)(i));
  return to;
}

template<typename T1, typename T2>
T2& distil(const T1& from, T2& to)
{
    std::copy(from.begin(), from.end(), std::back_inserter(to));
    return to;
}                                                            

struct WrapperAbstract
{
  virtual ~WrapperAbstract() {}
  virtual size_t count() const = 0;
  virtual B* get_element(size_t i) = 0;
  //virtual const B* get_element(size_t i) const = 0; FIXME HERE error because compiler cannot resolve overloading function
  // main.cpp:42:5: note:   template argument deduction/substitution failed:
  // main.cpp:88:74: note:   couldn't deduce template parameter ‘AccessF’
  // or
  // main.cpp:42:5: note: candidate template ignored: couldn't infer template argument 'AccessF'
  std::deque<B*> lb;
};

struct Wrapper : public WrapperAbstract
{
  static Wrapper getWrapper() { return Wrapper(); }
  Wrapper()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    for(int i = 0; i < 3; ++i)
      lb.push_back(new B(i));
  }
  ~Wrapper()
  {
    typedef std::deque<B*> C;
    for(C::const_iterator ci = lb.begin(); ci != lb.end(); ++ci)
      delete *ci;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  size_t count() const { return lb.size(); }
  B* get_element(size_t i) { return lb[i]; }
  //const B* get_element(size_t i) const { return lb[i]; }
};

int main()
{
  //std::list<B*> lb;
  //for(int i = 0; i < 3; ++i)
  //  lb.push_back(new B(i));
  //Wrapper w;
  WrapperAbstract* wp = new Wrapper();
  print_container(std::cout, wp->lb);
  //std::list<A*> la;
  //std::copy(lb.begin(), lb.end(), std::back_inserter(la));
  std::list<B*> lb;
  //collect(w, &Wrapper::get_element, &Wrapper::count, lb);
  collect(*wp, &WrapperAbstract::get_element, &WrapperAbstract::count, lb);
  print_container(std::cout, lb);

  std::list<A*> la;
  distil(lb, la);
  print_container(std::cout, la);
  std::list<A*> va;
  distil(lb, va);
  print_container(std::cout, va);
  delete wp;
}
