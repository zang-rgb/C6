/*
题目：求一个3*3矩阵对角线元素之和

程序分析：利用双重for循环控制输入二维数组，再将a[i][i]累加后输出。
*/

#include <stdio.h>

int main(void)
{
  int i, j, a[10][10], sum;

  for (i = 0; i < 4; i++)
    for(j = 0; j < 4; j++)
      scanf("%d", &a[i][j]);

  for (i = 0; i < 4; i++)
    for(j = 0; j < 4; j++)
      if (i == j)
        sum += a[i][j];
        
  printf("%d", sum);
  return 0;
}
