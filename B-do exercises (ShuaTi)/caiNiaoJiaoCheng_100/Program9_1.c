/*
题目：要求输出国际象棋棋盘。

程序分析：国际象棋棋盘由64个黑白相间的格子组成，分为8行*8列。用i控制行，j来控制列，根据i+j的和的变化来控制输出黑方格，还是白方格。
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void)
{
  char a = 219;
  SetConsoleOutputCP(437);
  int i, j;
  int row = 8, col = 8;
  for ( i = 0; i < row; i++)
  {
    for ( j = 0; j < col; j++)
    {
      if ((i+j)%2 == 0)
        printf("%c%c", a, a);
      else
        printf("  ");
    }
    printf("\n");
    
  }
  
  return 0;
}
