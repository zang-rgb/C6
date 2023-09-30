/*
题目：利用递归函数调用方式，将所输入的5个字符，以相反顺序打印出来。

程序分析：无。
*/

#include <stdio.h>
#define N 5
void func(char * str, int length);

int main(void)
{
  char * s = "hello";
  func(s, N);
  return 0;
}

//尾递归，它相当于循环
void func(char * str, int length)
{
  if (length >= 1)
  {
    printf("%c", str[length - 1]);
    func(str, length - 1);
  }
}