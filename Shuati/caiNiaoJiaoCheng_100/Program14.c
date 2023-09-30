/*
题目：将一个正整数分解质因数。例如：输入90,打印出90=2*3*3*5。

程序分析：用短除法求解。
对n进行分解质因数，应从i=2开始遍历，利用n % i == 0判断先找到一个最小的质数i，然后按下述步骤完成：
(1)如果这个最小质数恰等于n，则说明分解质因数的过程已经结束，n本身就是质数，打印出n即可。
(2)如果这个最小质数不等于n，则应打印出i的值，并用n除以i的商,作为新的正整数n，重新进入while循环。while循环判断操作不满足条件退出后，则进入for循环，i自增1后进入while循环判断操作，如此往复（注意此时for循环中n的值已经改变）
*/

#include <stdio.h>

int main(void)
{
  int n, i;
  printf("请输入整数：");
  scanf("%d", &n);
  printf("%d=", n);
  for ( i = 2; i <= n; i++)
  {
    while (n % i == 0)
    {
      printf("%d", i);          //原样输出
      n /= i;                   //根据短除法，用商作新的n,即被除数。接着重复while循环判断操作。
      if(n != 1)  printf("*");
    }
  }
  
  return 0;
}