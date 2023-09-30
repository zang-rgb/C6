#include <stdio.h>

int main(void)
{
  int days[] = { 31, 28, 21, 30, 31, 30, 31, 31, 30, 31 };
  int index;

  for (index = 0; index < (sizeof (days) / sizeof (days[0])); index++)
    printf("Month %2d has %d days.\n", index, days[index]);
  return 0;
}