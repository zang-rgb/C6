#include <stdio.h>
#include <stdbool.h>
long get_long(void);
bool bad_limits(long begin, long end, long low, long high);
double sum_squares(long a, long b);

int main(void)
{
  const long MIN = -10000000L;
  const long MAX = +10000000L;
  long start;
  long stop;  
  double answer;

  printf("This prigram computes the sum of the squares of integers in a range.\n");
  printf("The lower bound should not less than -10000000\n");
  printf("and the upper bound should not more than +10000000.\n");
  printf("Enter the limits (Enter 0 fot both limits to quit):\n");
  printf("Lower limits:\n");
  start = get_long();
  printf("Upper limit:\n");
  stop = get_long();
  while (start != 0 || stop != 0)
  {
    if (bad_limits(start, stop, MIN, MAX))
      printf("Try again.\n");
    else
    {
      answer = sum_squares(start, stop);
      printf("The sum of the squares of the integers ");
      printf("from %ld to %ld is %g.\n", start, stop, answer);
    }
    printf("Enter the limits (Enter 0 fot both limits to quit):\n");
    printf("Lower limits:\n");
    start = get_long();
    printf("Upper limit:\n");
    stop = get_long();
  }
  printf("Done!\n");

  return 0;
}





long get_long(void)
{
  long input;
  char ch;

  while (scanf("%ld", &input) != 1)
  {
    while ((ch = getchar()) != '\n')
      putchar(ch);
    printf(" is not an integer.\n");
    printf("Please enter an integer value, such as 25, -178, or 3\n");
  }

  return input;
}

bool bad_limits(long begin, long end, long low, long high)
{
  bool not_good = false;

  if (begin > end)
  {
    printf("%ld isn't smaller than %ld.\n", begin, end);
    not_good = true;
  }
  if (begin < low || end < low)
  {
    printf("Values must be %ld or greater.\n", low);
    not_good = true;
  }
  if (begin > high || end > high)
  {
    printf("Values must be %ld or less.\n", high);
    not_good = true;
  }

  return not_good;
}

double sum_squares(long a, long b)
{
  double total = 0;
  long i;

  for (i = a; i <= b; i++)
    total += (double) i * (double) i;
  
  return total;
}