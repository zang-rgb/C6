/*
题目：求1+2!+3!+...+20!的和。

程序分析：此程序只是把累加变成了累乘。
*/
#define printf __mingw_printf
#include <stdio.h>

int main(void)
{
  int i;
  int n = 20;
  long double sum, m;
  sum = 0; 
  m = 1;
  for (i = 1; i <= 20; i++)
  {
    m = m * i;
    sum += m;
  }
  printf("%Lf\n", sum); //long double用Lf（真值理论）
  return 0;
}