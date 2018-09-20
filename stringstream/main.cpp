#include <iostream>
#include <list>
#include <string>
#include <sstream>

int main()
{
  using namespace std;
  typedef list<string> stringlist;
  int i = 0;
  double d = 0;
  stringlist strs;
  strs.push_back("1323");
  strs.push_back("-132e3");
  strs.push_back("132a");
  strs.push_back("-132e3d");
  for(string s : strs)
  {
    stringstream si;
    si << s;
    si >> i;
    stringstream sd;
    sd << s;
    sd >> d;
    cout
      <<   "str: " << s
      << ", int: " << i
      << ", dbl: " << d
      << ", remain: " << si.str() << ", " << sd.str()
      << endl;
  }
}
