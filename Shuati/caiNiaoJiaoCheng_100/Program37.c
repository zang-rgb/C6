/*
题目：对10个数进行排序。

程序分析：可以利用选择法，即从后9个比较过程中，选择一个最小的与第一个元素交换， 下次类推，即用第二个元素与后8个进行比较，并进行交换。
*/

#include <stdio.h>

int main(void)
{
  int a[10] = {5,1,2,8,9,6,3,7,4,0};
  int i;
  int min, tmp;
  int j;
  for (i = 0; i < 10; i++)
  {
    min = i;    //每次进入外层for循环都要将min重置为当前外层循环数组下标，从当前数组下标元素开始与后面的元素进行比对，当前下标之前的元素已经排序完成。
    for (j = i + 1; j < 10; j++)
    {
      if (a[min] > a[j])
        min = j;    //min被重置为j后，还会继续进行内层for循环，执行j++，继续与后面的元素进行比较大小，如果继续出现比后面的大，min将再次被重新赋值，直到找出最小值
    }
    if (min != i)   //条件为真，说明min被重置，当前i不是最小值，将当前i与最小值min对换
    {
      tmp = a[min];
      a[min] = a[i];
      a[i] = tmp;
    }
  }

  for (i = 0; i < 10; i++)
    printf("%d  ", a[i]);
  
  return 0;
}