/*
题目：输出特殊图案，请在c环境中运行，看一看，Very Beautiful!

程序分析：字符共有256个。不同字符，图形不一样。
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void)
{
    int i, j;
    char a = 176, b = 219;
    SetConsoleOutputCP(437);

    for ( i = 0; i < 5; i++)
    {
      for (j = 0; j < 5; j++)
      {
        if (i == j || (i + j + 1 == 5))
          printf("%c", b);
        else
          printf("%c", a);
      }
      printf("\n");
    }
    
    return 0;
}