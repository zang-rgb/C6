/*
 *题目：打印楼梯，同时在楼梯上方打印两个笑脸。

 *程序分析：用 ASCII 1 来输出笑脸；用i控制行，j来控制列，j根据i的变化来控制输出黑方格的个数。
 */

#include <stdio.h>
#include <windows.h>

int main(void)
{
  char a = 219;
  SetConsoleOutputCP(437);
  int i, j;
  int row = 9;

  printf("\1\1\n");
  for ( i = 0; i < row; i++)
  {
    for ( j = 0; j <= i; j++)
      printf("%c%c", a, a);
    printf("\n"); 
  }
  
  return 0;
}