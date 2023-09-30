#include <stdio.h>
#include <string.h>
#define FUNDLEN 50

struct funds
{
  char banks[FUNDLEN];
  double bankfund;
  char save[FUNDLEN];
  double savefund;
};

double sum(const struct funds *);

int main(void)
{
  struct funds stan = {
    "Garlic-Melon Bank",
		4032.27,
		"Lucky's Savings and Loan",
		8543.94
  };

  printf("%.2f", sum(&stan));

  return 0;
}


double sum(const struct funds * money)
{
  return (money -> bankfund + money -> savefund);
}
