/*
题目：求100之内的素数。

程序分析：质数（prime number）又称素数，有无限个。一个大于1的自然数，除了1和它本身外，不能被其他自然数整除。
*/

#include <stdio.h>

int main(void)
{
  int i, j;
  int Flag
  for(i = 2; i < 100; i++)
  {
    Flag = 1;   //每次进入外层for循环都要将Flag位重新置为1
    for (j = 2; j < i; j++)
    {
      if (i % j == 0)
        Flag = 0;
    }
    if (Flag == 1)
      printf("%d  ", i);
  }
  return 0;
}