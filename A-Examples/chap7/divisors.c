//divisors.c -- 使用嵌套if语句显示一个数的约数
#include <stdio.h>
#include <stdbool.h>
int main(void)
{
  unsigned long num;
  unsigned long div;
  bool isPrime;

  printf("Please enter an integer for analysis; ");
  printf("Enter q to quit.\n");
  while (scanf("%d", &num) == 1)
  {
    for (div = 2, isPrime = true; (div*div) <= num; div++)
    {
      if (num % div == 0)
      {
        if ((num/div) != div)
          printf("%d is divisible by %d and %d.\n",
                num, div, num/div);
        else 
          printf("%d is divisble by %d\n", num, div);
        isPrime = false;
      }
    }
    if (isPrime == true)
        printf("%d is a prime.\n", num);
    printf("Please enter another integer for analysis; ");
    printf("Enter q to quit.\n");
  }
  printf("bye.\n");
  return 0;
}