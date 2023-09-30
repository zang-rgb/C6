/*wheat.c -- 指数增长*/
#include <stdio.h>
#define SQUARES 64
int main(void)
{
  const double CROP = 2E16; // 世界小麦年产谷粒数
  double current, total;
  int count = 1;

  printf("square   grains       total        ");
  printf("fraction of \n");
  printf("         added        grains       ");
  printf("world total\n");

  total = 1.0;
  current = 1.0;
  printf("%4d %13.2e %12.2e %12.2e\n", count, current, total, total/CROP);
  while (count < 65)
  {
    count = count + 1;
    current = current * 2;
    total = current + total;
    printf("%4d %13.2e %12.2e %12.2e\n", count, current, total, total/CROP);
  }

  return 0;
} 