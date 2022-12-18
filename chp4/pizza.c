#include<stdio.h>
#define PI 3.14159 //基本上是一个固定的值 1.一改全改，2.可读性好
int main(void)
{
  float area, circum, radius;//面积，周长，半径

  printf("What is the radius of your pizza?\n");
  scanf("%f", &radius);

  area = PI * radius * radius;
  circum = 2.0 * PI * radius;

  printf("Your basic pizza parameters are as follows:\n");
  printf("circumference = %1.2f, area = %1.2f\n", circum, area);
  return 0;
}