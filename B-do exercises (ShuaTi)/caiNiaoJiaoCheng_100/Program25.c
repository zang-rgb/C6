/*
题目：求1+2!+3!+...+20!的和。

程序分析：此程序只是把累加变成了累乘。
*/

#include <stdio.h>
#define printf __mingw_printf
#define N 20

int main(void)
{
  long double mix, sum;
  mix = 1;
  sum = 0;
  for (int i = 1; i <= N; i++)
  {
    mix *= i;
    sum += mix;
  }
  printf("%Lf", sum);
  return 0; 
}