/*
题目：输入两个正整数m和n，求其最大公约数和最小公倍数。

程序分析：

（1）最小公倍数=输入的两个数之积除于它们的最大公约数，关键是求出最大公约数；

（2）求最大公约数用辗转相除法(中国叫法), 也叫欧几里得算法(国外叫法)。

  该算法定义如下：两个正整数A，B的最大公约数等于其中较小值与两数相除的余数的最大公约数。
  该算法实现步骤如下：
  设有两整数a和b：
  (1) a%b得余数c
  (2) 若c==0，则b即为两数的最大公约数
  (3) 若c！=0，则a=b，b=c，再回去执行第一步。
*/

#include <stdio.h>

int main(void)
{
  int a, b, c, max, min, tmp;
  printf("Enter two numbers:");
  scanf("%d %d", &a, &b);
  tmp = a*b;
  c = a%b;
  while (c != 0)
  {
    a = b;
    b = c;
    c = a % b;
  }

  max = b;
  min = tmp / b;

  printf("max = %d, min = %d\n", max, min);

   
  return 0;
}