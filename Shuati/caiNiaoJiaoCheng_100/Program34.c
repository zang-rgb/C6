/*
题目：练习函数调用。
*/

#include <stdio.h>

void one_hello();
void three_hello(int n);

int main(void)
{
  printf("Enter:");
  int n;
  scanf("%d" ,&n);
  three_hello(n);
  return 0;
}

void one_hello()
{
  printf("hello, world!\n");
}

void three_hello(int n)
{
  while (n--)
    one_hello();
}