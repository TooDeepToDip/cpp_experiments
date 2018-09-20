#include <utility>
#include <iostream>
#include <map>
#include "debug_helpers.h"

int main()
{
  //using debug::operator<<; // if operator<< defined in namespace
  std::cout << std::make_pair(2, 3) << std::endl;
  std::map<int, std::string> m;
  m[1] = "ham";
  m[2] = "spam";
  m[3] = "go";
  debug::print_map(std::cout, m);
}
