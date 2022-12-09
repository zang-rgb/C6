#include <stdio.h>
int main(void)
{
  float num;

  printf("Enter a Floating-pointing value:");
  scanf("%f", &num);
  printf("fixed-point notation: %f\n", num);
  printf("exponential notation: %e\n",num);
  return 0;
}