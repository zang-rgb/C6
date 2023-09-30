/*
题目：输出9*9口诀
*/
#include <stdio.h>

int main(void)
{
  int i, j;
  
  for ( i = 1; i < 10; i++)       //行
  {
    for ( j = 1; j < i + 1; j++)  //列
    {
      printf("%d * %d = %2d   ", j, i, i*j);
    }
    printf("\n");
    
  }
  
  return 0;
}