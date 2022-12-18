#include <stdio.h>
#include <float.h>
int main(void)
{
  double d = 1.0/3.0;
  float f = 1.0/3.0f;
  printf("%.6f %.6f\n", d, f);
  printf("%.12f %.12f\n", d, f);
  printf("%.16f %.16f\n", d, f);
  printf("%d %d\n", DBL_DIG, FLT_DIG);

  return 0;
}