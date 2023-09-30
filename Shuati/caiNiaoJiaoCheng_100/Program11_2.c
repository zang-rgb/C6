/*
题目：古典问题（兔子生崽）：有一对兔子，从出生后第3个月起每个月都生一对兔子，小兔子长到第三个月后每个月又生一对兔子，假如兔子都不死，问每个月的兔子总数为多少？（输出前40个月即可）

程序分析：兔子的规律为数列1,1,2,3,5,8,13,21....，即下个月是上两个月之和（从第三个月开始）。

斐波那契数列递归算法
*/

#include <stdio.h>
#define N 100

unsigned long long fib(int n)
{
  if (n == 1 || n == 2)
    return 1;
  else
    return fib(n - 2) + fib(n - 1);
}

int main(void)
{
  int i;
  for ( i = 1; i <= N; i++)
  {
    printf("%12lld", fib(i));
    if (i % 4 == 0) printf("\n");
  }
  
  return 0;
}
