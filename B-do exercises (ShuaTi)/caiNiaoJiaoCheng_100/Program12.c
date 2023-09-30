/*
题目：判断 101 到 200 之间的素数。

程序分析：判断素数的方法：用一个数分别去除 2 到 sqrt(这个数)，如果能被整除，则表明此数不是素数，反之是素数。
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
  int i, j, k;
  for (i = 101; i < 201; i++)
  {
    k = sqrt(i);                //如果i不能被2~√i间任一整数整除，i必定是素数
    for (j = 2; j <= k; j++)
    {
      if (i % j == 0)
        break;
    }
    if (j > k)
      printf("%d  ",i);
  }
  
  return 0;
}