/*伸缩型数组成员*/
#include <stdio.h>
#include <stdlib.h>

struct flex
{
  int count;
  double average;
  double score[];
};

void showFlex(const struct flex * p);

int main(void)
{
  struct flex * pf1, * pf2;
  int n = 5;
  int i;
  int tot = 0;

  pf1 = malloc(sizeof(struct flex) + n * sizeof(double));
  pf1 -> count = n;
  for (i = 0; i < n; i++)
  {
    pf1 -> score[i] = 20 - i;
    tot+= pf1 -> score[i];
  }
  pf1 -> average = tot / n;
  showFlex(pf1);

  n = 9;
  tot = 0;
  pf2 = malloc(sizeof(struct flex) + n * sizeof(double));
  pf2 -> count = n;
  for (i = 0; i < n; i++)
  {
    pf2 -> score[i] = 20 - i;
    tot+= pf2 -> score[i];
  }
  pf2 -> average = tot / n;
  showFlex(pf2);

  free(pf1);
  free(pf2);
  return 0;
}


void showFlex(const struct flex * p)
{
  int i;
  printf("Scores: ");
  for (i = 0; i < (p -> count); i++)
    printf("%g ", p -> score[i]);
  printf("\nAverage: %g\n", p -> average);

}
