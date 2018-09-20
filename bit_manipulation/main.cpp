#include <iostream>
#include <iomanip>

void print_int(int i)
{
  std::cout << "bits: "
    //<< std::showbase
    << std::hex
    << std::setw(8)
    << std::setfill('\x30')
    << i
    << std::endl;
}

#define print(x) \
  std::cout << ""#x" "; \
  print_int(x);

/// Pack values into int (I think std::vector<bool> makes
//  aproximately the same things)
int main()
{
  int a = 4;
  int b = 16; // if value is more than 2^(half_size - 1) you loss bits
  int c = 0;
  int pattern = ~0;
  //int half_size = sizeof(int)/2;
  pattern <<= sizeof(pattern) * 8/2;
  pattern = ~pattern;
  print(a);
  print(b);
  print(c);
  print(pattern);
  c |= a & pattern;
  print(c);
  c <<= sizeof(c) * 8/2;
  print(c);
  c |= b & pattern;
  print(c);
  int b1 = c & pattern;
  print(b1);
  c >>= sizeof(c) * 8/2;
  int a1 = c & pattern;
  print(a1);
}
