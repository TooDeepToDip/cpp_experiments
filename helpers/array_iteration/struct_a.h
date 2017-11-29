#ifndef STRUCT_A_H
#define STRUCT_A_H

#include <iostream>

struct A
{
  int a;
  char b;
};

bool operator==(const A& lhs, const A& rhs)
{
  return lhs.a == rhs.a and lhs.b == rhs.b;
}

std::ostream& operator<<(std::ostream& out, const A& a)
{
  return out << "{ " << a.a << ", " << a.b << " }";
}

#endif /* STRUCT_A_H */
