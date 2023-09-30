/*
题目：古典问题（兔子生崽）：有一对兔子，从出生后第3个月起每个月都生一对兔子，小兔子长到第三个月后每个月又生一对兔子，假如兔子都不死，问每个月的兔子总数为多少？（输出前40个月即可）

程序分析：兔子的规律为数列1,1,2,3,5,8,13,21....，即下个月是上两个月之和（从第三个月开始）。

斐波那契数列非递归算法
*/

#include <stdio.h>
#define MAX 40

int main(void)
{
  int month[MAX + 1];
  month[0] = 0;
  month[1] = 1;
  month[2] = 1;
  int i;

  for ( i = 3; i < MAX + 1; i++)
    month[i] = month[i - 2] + month[i - 1];
  
  for ( i = 1; i < MAX + 1; i++)
  {
    printf("%12d", month[i]);
    if (i % 4 == 0) printf("\n");
  }
  
  
  return 0;
}