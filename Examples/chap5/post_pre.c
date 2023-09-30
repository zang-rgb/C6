/*post_pre.c -- 前缀和后缀*/
//post 表示在后面
#include <stdio.h>
int main(void)
{
  int a = 1, b = 1;
  int a_post, pre_b;
  a_post = a++;
  pre_b = ++b;
  printf("a a_post b pre_b\n");
  printf("%d %6d %d %5d\n", a, a_post, b, pre_b);

  return 0;
}