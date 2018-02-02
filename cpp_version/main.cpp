#include <cstdio>

int main()
{
  printf("cpp version = %ld\n", __cplusplus);
#if __cplusplus > 199711L
  printf("wow! cpp version = %ld\n", __cplusplus);
#endif
}
