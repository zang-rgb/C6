#include <stdio.h>
int main(void)
{
  int count, sum;
  int days;
  count = 1;
  sum = 0;
  printf("Please enter days: ");
  scanf("%d", &days);
  while (days > 0)
  {
    sum = sum + count;
    count++;
    days--;
  }
  printf("$%d\n", sum);
  return 0;
  
}