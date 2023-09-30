/*
题目：利用递归方法求5!。

程序分析：递归公式：fn=fn_1*4!
*/

#include <stdio.h>
#define N 5
int fact(int a);

int main(void)
{
  printf("%d", fact(N));
  return 0;
}

int fact(int a)
{
  int sum;
  if (a == 0)
    sum = 1;
  else{
    sum = a * fact(a - 1);
  }
  return sum;
}