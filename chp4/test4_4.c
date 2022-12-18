#include <stdio.h>
int main(void)
{
  float height;
  char name[40];

  printf("Please enter your height in centimeter and name.\n");
  scanf("%f %s", &height, name);
  printf("%s, you are %.2f metre tall", name, height/100);

  return 0;
}