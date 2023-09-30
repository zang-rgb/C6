#include <stdio.h>
#define M_PER_H 60
int main(void)
{
  int time, hour, min;
  printf("Enter the number of minutes to convert: ");
  scanf("%d", &time);
  while (time > 0)
  {
    hour = time / M_PER_H;
    min = time % M_PER_H;
    printf("%d times = %d hours %d minutes\n", time, hour, min);
    printf("Enter next minutes value (0 to quit): ");
    scanf("%d", &time);
  }
  printf("Please enter time > 0");
  return 0;
  
}