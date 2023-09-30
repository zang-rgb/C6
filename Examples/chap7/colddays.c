//colddays.c -- 找出0℃以下的天数占总天数的百分比
#include <stdio.h>
int main(void)
{
  const int FREEZING = 0;
  int temp;
  int days = 0;
  int sum = 0;

  printf("Enter the lowest temp. ");
  printf("Enter q to quit.\n");
  while (scanf("%d", &temp) == 1)
  {
    days++;
    if (temp < FREEZING)
    {
      sum++;
    }
  }
  printf("days = %d\n", days);
  printf("sum = %d\n", sum);
  return 0;

}