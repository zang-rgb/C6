/*
题目：有一个已经排好序的数组。现输入一个数，要求按原来的规律将它插入数组中。

程序分析：首先判断此数是否大于最后一个数,然后再考虑插入中间的数的情况,插入后此元素之后的数,依次后移一个位置。
*/

#include <stdio.h>

int main(void)
{
  int a[11] = {1, 4, 6, 9, 13, 16, 19, 28, 40, 100};
  int number, i;
  int liucun, temp, j;
  printf("RAW: ");
  for (i = 0; i < 10; i++)
    printf("%d ", a[i]);
  printf("\n");
  printf("Enter:");
  scanf("%d", &number);

  if (number > a[9])
    a[10] = number;
  else
  {
    for (i = 0; i < 10; i++) // 先写伪代码，再实现
    {
      if (a[i] > number)
      {
        liucun = a[i];
        a[i] = number;
        for (j = i; j < 10; j++)
        {
          temp = a[j + 1];
          a[j + 1] = liucun;
          liucun = temp; // liucun相当于a[j]，不断更新，通过它和a[j + 1]互换来实现a[j]变成a[j + 1]，temp相当于互换用容器
        }
        break;
      }
    }
  }

  for (i = 0; i < 11; i++)
    printf("%4d", a[i]);

  return 0;
}