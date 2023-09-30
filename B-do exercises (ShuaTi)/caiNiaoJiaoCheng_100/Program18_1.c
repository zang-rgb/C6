/*
题目：求s=a+aa+aaa+aaaa+aa...a的值，其中a是一个数字。例如2+22+222+2222+22222(此时共有5个数相加)，几个数相加有键盘控制。

程序分析：有5个2，4个20，3个200，2个2000,1个20000 相加
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
  int a, n;
  int sum = 0;

  printf("input a and n:");
  scanf("%d %d", &a, &n);

  for (int i = 0; i < n; i++)
  {
    sum += a * pow(10, i) * (n - i);
  }

  printf("a+aa+...=%d\n", sum);

  return 0;
}