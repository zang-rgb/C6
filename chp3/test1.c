#include <stdio.h>
int main(void)
{
  char ch;

  printf("Enter an ASCII code:");
  scanf("%d", &ch);
  printf("%d is the ASCII code for %c.\n", ch, ch);
  return 0;
}