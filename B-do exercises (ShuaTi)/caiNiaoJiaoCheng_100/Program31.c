/*
题目：请输入星期几的第一个字母来判断一下是星期几，如果第一个字母一样，则继续判断第二个字母。

程序分析：用情况语句比较好，如果第一个字母一样，则判断用情况语句或if语句判断第二个字母。
*/

#include <stdio.h>

int main(void)
{
  printf("输入一个礼拜首字母");
  char i, j;
  scanf("%c", &i);
  getchar();
  switch (i)
  {
  case 'm':
    printf("monday\n");
    break;

  case 't':
    printf("输入一个礼拜第二个字母");
    scanf("%c", &j);
    switch (j)
    {
    case 'u':
      printf("tuesday\n");
      break;
    case 'h':
      printf("thursday\n");
      break;
    default:
      break;
    }
    break;

  case 'w':
    printf("wednesday\n");
    break;

  case 'f':
    printf("friday\n");
    break;

  case 's':
    printf("输入一个礼拜第二个字母");
    scanf("%c", &j);
    switch (j)
    {
    case 'a':
      printf("saturday\n");
      break;
    case 'u':
      printf("sunday\n");
      break;
      
    default:
      printf("error\n");
      break;
    }
    break;

  default:
    break;
  }
  return 0;
}