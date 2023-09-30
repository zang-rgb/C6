//min_sec.c -- 把秒数转换为分钟和秒
#include <stdio.h>
#define SEC_PER_MIN 60 //1分钟60秒
int main(void)
{
  int sec, min, left;
  
  printf("Convert seconds to minutes and seconds.\n");
  printf("Enter the number of seconds(<=0 to qiut):\n");
  scanf("%d", &sec);
  while (sec > 0)
  {
    min = sec / SEC_PER_MIN;
    left = sec % SEC_PER_MIN;
    printf("%d seconds is %d minutes and %d seconds.\n", sec, min, left);
    printf("Enter next seconds(<=0 to qiut):\n");
    scanf("%d", &sec);
  }
  printf("Done!\n");
  
  return 0;
}