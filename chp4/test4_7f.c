/* Programming Exercise 4-7 */
#include <stdio.h>
#include <float.h>
int main(void)
{
 float ot_f = 1.0 / 3.0;
 double ot_d = 1.0 / 3.0;
 printf(" float values: ");
 printf("%.4f %.12f %.16f\n", ot_f, ot_f, ot_f);
 printf("double values: ");
 printf("%.4f %.12f %.16f\n", ot_d, ot_d, ot_d);
 printf("FLT_DIG: %d\n", FLT_DIG);
 printf("DBL_DIG: %d\n", DBL_DIG);
 return 0;
}