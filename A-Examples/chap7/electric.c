//electric.c -- 计算电费
#include <stdio.h>
#define RATE1 0.13230
#define RATE2 0.15040
#define RATE3 0.30025
#define RATE4 0.34025
#define BREAK1 360
#define BREAK2 468
#define BREAK3 720
#define BASE1 BREAK1 * RATE1
#define BASE2 BASE1 + (BREAK2 - BREAK1)*RATE2
#define BASE3 BASE2 + (BREAK3 - BREAK2)*RATE3
int main(void)
{
  double kwh;
  double bill;
  scanf("%lf", &kwh);
  if (kwh < BREAK1)
    bill = kwh * RATE1;
  else if (kwh < BREAK2)
    bill = BASE1 + (kwh - BREAK1)*RATE2;
  else if (kwh < BREAK3)
    bill = BASE2 + (kwh - BREAK2)*RATE3;
  else
    bill = BASE3 + (kwh - BREAK3)*RATE4;
  printf("The charge for %.1f kwh is $%.2f.\n", kwh, bill);
  return 0;

}