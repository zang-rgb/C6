/*测试rand1()和srand1()*/
#include <stdio.h>
#include <stdlib.h>
extern int rand1(void);
extern void srand1(unsigned int seed);

int main(void)
{
  int count;
  unsigned seed;
  printf("Enter your choice for seek(q to quit):");
  while (scanf("%u", &seed) == 1)
  {
    srand1(seed);
    for(count = 0; count < 5; count++)
      printf("%d\n", rand1());
    printf("Enter next seed, (q to quit):\n");
  }
  printf("Done!");
  return 0;
}