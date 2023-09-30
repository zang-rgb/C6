/*shes1.c -- 计算多个不同鞋码对应的脚长*/
#include <stdio.h>
#define ADJUST 7.31; //字符常量、明示常量
int main(void)
{
  const double SCALE = 0.333; //const变量
  double shoe, foot;

  shoe = 3.0;
  while (shoe < 18.5)
  {
    foot = SCALE * shoe + ADJUST;
    //printf(" Shoe size (men's)   foot length\n");
    printf("%10.1f %15.2f inches\n", shoe, foot);
    shoe = shoe + 1;
  }
  printf("If the shoe fits, wear it.\n");
  
  return 0;
}