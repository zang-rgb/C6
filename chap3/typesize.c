#include <stdio.h>
int main(void)
{
  printf("Type char has a size of %d bytes.\n", sizeof(char));
  printf("Type short has a size of %d bytes.\n", sizeof(short));
  printf("Type int has a size of %d bytes.\n", sizeof(int));
  printf("Type long has a size of %d bytes.\n", sizeof(long));
  printf("Type long long has a size of %d bytes.\n", sizeof(long long));

  printf("\n");

  printf("Type float has a size of %d bytes.\n", sizeof(float));
  printf("Type double has a size of %d bytes.\n", sizeof(double));
  printf("Type long double has a size of %d bytes.\n", sizeof(long double));

  getchar();
  

  return 0;
} 