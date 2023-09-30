#include <stdio.h>

int main(void)
{
  int i;
  scanf("%d", &i);
  if (i > 0)
    printf("zhenshu");
  else if (i < 0)
    printf("fu");
  else 
    printf("ling");
  return 0;
}