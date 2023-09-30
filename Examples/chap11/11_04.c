#include <stdio.h>
#define SLEN 40
#define LIM  5
int main(void)
{
  const char *mytalents[LIM] = {
    "Adding",
    "Multiplying", "Stashing",
    "Following",
    "Understanding"
  };
  char yourtalents[LIM][SLEN] = {
    "Walking",
    "Sleeping",
    "Watching",
    "Mailing", "Reading"
  };
  int i;

  puts("Let's compare talents");
  printf("%-36s  %-25s\n", "Mytalents", "Yourtalents");
  for (i = 0; i < LIM; i++)
    printf("%-36s  %-25s\n", mytalents[i], yourtalents[i]);
  printf("%-36d  %-25d\n", sizeof(mytalents), 
    sizeof(yourtalents));

  return 0;
}