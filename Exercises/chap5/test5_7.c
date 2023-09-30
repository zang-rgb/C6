#include <stdio.h>
void showCube(double db);
int main(void)
{
  double db;
  printf("Enter a floating-point value: ");
  scanf("%lf", &db);
  showCube(db);
  return 0;
}

void showCube(double x)
{
  printf("The cube of %e is %e.\n", x, x*x*x);
}