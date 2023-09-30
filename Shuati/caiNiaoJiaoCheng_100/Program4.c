/*
题目：输入某年某月某日，判断这一天是这一年的第几天？

程序分析：以3月5日为例，应该先把前两个月的加起来，然后再加上5天即本年的第几天，特殊情况，闰年且输入月份大于3时需考虑多加一天。
*/

#include <stdio.h>

int main(void)
{
  int year, month, day;
  int monthdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int i, sumdays = 0;

  printf("year,month,day:");
  scanf("%d,%d,%d", &year, &month, &day);

  if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
    monthdays[1] = 29;

  for ( i = 0; i < month-1; i++)
  {
    sumdays += monthdays[i];
  }
  sumdays += day;

  printf("%d", sumdays);
  return 0;
}