#include <iostream>
// see http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#136

//Q:
// Following code is correct? If yes, why? In no, how to fix it?
//
//namespace some_ns {
//  class some_class {
//    friend int some_function(int arg = 0);
//  };
//}

//A: (maybe incorrect)

namespace some_ns {
int some_function2(int arg = 0); // #tag3
}

namespace some_ns {
  class some_class {
    int i;
    friend int some_function(some_class* c, int arg = 0) { return c->i + arg;} // because ADL (#tag1)
    friend int some_function2(int arg){ return arg;} // but friend declaration isn't declaration (see #tag2)
    public:
    some_class(int i) : i(2 * i) {}
    int foo() const { return i; }
  };
}

int main()
{
  some_ns::some_class c(3);
  std::cout << "f1 = " << some_function(&c, 1) << std::endl; // #tag1 can find function
  std::cout << "f2 = " << some_function(&c) << std::endl;
  std::cout << "f3 = " << some_ns::some_function2() << std::endl; // #tag2 therefore function is inaccessible without declaration #tag3
}
