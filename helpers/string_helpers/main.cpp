#include <iostream>
#include "string_helpers.h"

#define PRINT(num, x) \
  std::cout << num << ": " << #x" = " << x << std::endl;

void trim()
{
  using std::string;
  using namespace string;
  string a = " \t  \n some important text \n \t\n   \t";
  string b = a;
  string c = a;
  PRINT(0, a);
  std::cout << "1: " << "'" << ltrim(a) << "'" << std::endl;
  std::cout << "2: " << "'" << rtrim(b) << "'" << std::endl;
  std::cout << "3: " << "'" <<  trim(c) << "'" << std::endl;
}

void split_join()
{
  using std::string;
  using namespace string;
  string a = "bla bla bla car";
  stringlist l = split(a, " ");
  std::cout << "1: " << "'" << l.back() << "'" << std::endl;
  std::cout << "2: " << "'" << contains(a, "car") << "'" << std::endl;
  l.pop_back();
  std::cout << "3: " << "'" << join(l, "-") << "'" << std::endl;
  std::cout << "4: " << "'" << contains(join(l, "-"), "car") << "'" << std::endl;
}

void modify()
{
  using namespace string;
  std::cout << "1: " << "'" << from(1385) << "'" << std::endl;
  std::cout << "2: " << "'" << to_upper("sudo!") << "'" << std::endl;
}

void replace_string()
{
  using std::string;
  using namespace string;
  string a = "eat more this switty and pretty spams and eggs";
  string b = "съешь 'еще' 'этих' вкусных и свежих булочек";
  std::cout << "1: " << "'" << replace(a, "more", "less") << "'" << std::endl;
  std::cout << "2: " << "'" << replace(a, "switty", "grenny") << "'" << std::endl;
  std::cout << "3: " << "'" << replace(a, "pretty", "nicy") << "'" << std::endl;
  std::cout << "4: " << "'" << replace(a, "drums", "drugs") << "'" << std::endl;
  std::cout << "5: " << "'" << replace("", "drums", "drugs") << "'" << std::endl;
  std::cout << "6: " << "'" << replace(b, "этих", "тех") << "'" << std::endl;
  std::cout << "7: " << "'" << replace(b, "еще", "больше") << "'" << std::endl;
}

int main()
{
  trim();
  split_join();
  modify();
  replace_string();
}
