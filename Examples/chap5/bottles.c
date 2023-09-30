#include <stdio.h>
#define MAX 100
int main(void)
{
  int count = MAX + 1;

  while (--count > 0)
  {
    printf("%d bottles of spring water on the wall, "
            "%d bottles of spring water!\n", count, count);
    printf("%d bottles of spring water!\n", count - 1);
  }

  return 0;
}