/*addemup.c -- 几种常见的语句*/
#include <stdio.h>
int main(void)
{
  /*
  int count, sum;
  
  count = 1;
  sum = 0;
  while (count <= 20)
  {
    sum = sum + count;
    count++; 
  }
  printf("sum = %d", sum);

  return 0;
  */

 int count, sum;

 count = 0;
 sum = 0;

 while (count++ < 20)
 {
    sum = count + sum;
 }
  printf("sum = %d", sum);
 return 0;
 

}