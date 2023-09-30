#include <stdio.h>
int main(void)
{
  const int D_PER_W = 7;
  int days;
  int w, d;

  printf("Enter the number of days to convert: ");
  scanf("%d", &days);
  while (days > 0)
  {
    w = days / D_PER_W;
    d = days % D_PER_W;
    printf("%d days are %d weeks, %d days\n", days, w, d);
    printf("Enter next minutes value (0 or less to end): ");
    scanf("%d", &days);
  }
  printf("Done!\n");
  return 0;
}