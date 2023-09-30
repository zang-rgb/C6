/*hotel.c -- 酒店管理函数*/
#include <stdio.h>
#include "hotel.h"

int menu(void)
{
  int code, status;
  printf("\n%s%s\n", STARS, STARS);
  printf("Enter the number of the desired hotel:\n");
  printf("1) Fairfield Arms     2) Hotel Olympic\n");
  printf("3) Chertworthy Plaza  4) The Stockton\n");
  printf("5) quit.\n");
  printf("%s%s\n", STARS, STARS);
  while ((status = scanf("%d", &code)) != 1 || (code < 1 || code > 5))
  {
    if (status != 1)
      printf("%*s");
    printf("Enter an integer from 1 to 5, please.\n");
  }

  return code;
}

int getnights(void)
{
  int nights, status;

  printf("How many nights are needed?\n");
  while (((status = scanf("%d", &nights) )!= 1) || (nights < 0))
  {
    if (status != 1)
      printf("%*s");
    printf("Enter an positive integer such as 2, please.\n");
  }

  return nights;
}

void showprice(int nights, double rate)
{
  int n;
  double total = 0.0;
  double factor = 1.0;
  for (n = 1; n <= nights; n++, factor *= 0.95)
    total += rate * factor;
  printf("The total cost will be $%0.2f", total);
}