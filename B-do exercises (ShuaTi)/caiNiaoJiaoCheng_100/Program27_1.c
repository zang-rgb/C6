#include <stdio.h>
#define N 5

void func(char * p, int n);

int main(void)
{
  char a[N + 1] = "abcde";
  func(a, N);
  return 0;
}

void func(char * p, int n)
{
  if (n == 0)
    return;
  func(p, n-1);
  printf("%c\n", p[N - n]);
  return;
}