/*
题目：字符串反转，如将字符串 "www.runoob.com" 反转为 "moc.boonur.www"。

程序分析：无。
*/

#include <stdio.h>
#include <string.h>

void reverse(char  * p);

int main(void)
{
  char string[] = "www.runoob.com";
  puts(string);
  reverse(string);
  puts(string);
  return 0;
}

void reverse(char  * p)
{
  char * tmp;
  char * begin, * end;
  int len;
  len = strlen(p);
  begin = p;
  end = p + len - 1;
  while (begin < end)   //字符串是字符数组，数组在内存中是连续存储的
  {
    *tmp = *begin;
    *begin = *end;
    *end = *tmp;
    begin++;
    end--;
  }
}