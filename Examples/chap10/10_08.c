#include <stdio.h>

#define SIZE 4

int main(void)
{
  short dates[SIZE];
  short * pti;
  short index;

  double bills[SIZE];
  double * ptr;

  pti = dates;
  ptr = bills;

  printf("%23s %15s\n", "short", "double");
  for (index = 0; index < SIZE; index++)
    printf("pointers + %hd: %10p %10p\n", index, pti + index, ptr + index);

  return 0;
}