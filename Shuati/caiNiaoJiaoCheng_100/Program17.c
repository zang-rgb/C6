/*
题目：输入一行字符，分别统计出其中英文字母、空格、数字和其它字符的个数。

程序分析：利用while语句,条件为输入的字符不为'\n'。
*/

#include <stdio.h>

int main(void)
{
  char c;
  int letters=0, spaces=0, numbers=0, others=0;

  printf("input:");
  while ((c = getchar()) != '\n')
  {
    if ((c > 'a' && c < 'z') ||(c > 'A' && c < 'Z'))
      letters++;
    else if (c > '0' && c < '9')
      numbers++;
    else if (c == ' ')
      spaces++;
    else 
      others++;
  }

  printf("%5d%5d%5d%5d", letters, numbers, spaces, others);

  return 0;
}