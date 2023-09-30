//useheader.c -- 使用names_st结构

#include <stdio.h>
#include "1606names_st.h"

int main(void)
{
  names condidate;

  get_names(&condidate);
  printf("Let's welcome ");
  show_names(&condidate);
  printf(" to this program!\n");
  getchar();
  return 0;
}