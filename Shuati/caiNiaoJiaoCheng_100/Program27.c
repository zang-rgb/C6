#include <stdio.h>

void palin(int n);

int main(void)
{
  int i=5;
  printf("请输入5个字符\40:\40");
  palin(i);
  return 0;
}

void palin(int n)
{
  char next;
  if (n <= 1)
  {
    next = getchar();
    putchar(next);
  }
  else{
    next = getchar();
    palin(n - 1);
    putchar(next);
  }
}
