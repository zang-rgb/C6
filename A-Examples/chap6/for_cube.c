//dor_cube.c -- 使用for循环创建一个立方表
#include <stdio.h>
int main(void)
{
  int n;
  printf("n      n_cubed\n");
  for (n=1; n<=6; n++)
  {
    printf("%d %9d\n", n, n*n*n);
  }

  return 0;
}