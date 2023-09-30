/*squares.c -- 计算1~20的平方*/
#include <stdio.h>
int main(void)
{
  int num = 1;

  while (num < 21)
  {
    printf("   %d = %d * %d\n", num*num, num, num);
    num = num + 1;
  }

  return 0;
}