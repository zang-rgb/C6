/*
题目：判断一个数字是否为质数。

程序分析：质数（prime number）又称素数，有无限个。一个大于1的自然数，除了1和它本身外，不能被其他自然数整除。
*/

#include <stdio.h>
#include <math.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

int main(void)
{
  while(1)
  {
    int n;
    printf("Enter, 0 to quit:");
    scanf("%d", &n);
    int i;
    BOOL flag = TRUE;
    for (i = 2; i < n; i++)
    {
      if (n%i == 0)
      {
        printf("Not prime.\n");
        flag = FALSE;
        break;
      }  
    }
    if (n != 0 && (flag == TRUE || n == 1 || n == 2))
      printf("prime.\n");  
    if (n == 0)
    {
      printf("end.");
      break;
    }
      
  } 
  return 0;
}