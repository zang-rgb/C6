/*manydice.c  多次掷骰子的模拟程序*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "1212diceroll.h"

int main(void)
{
  int dice;
  int sides;
  int roll;
  int status;

  srand((unsigned int) time(0));
  printf("How many sides? Enter 0 to quit.\n");
  while ((scanf("%d", &sides)) == 1 && sides > 0)
  {
    printf("How many dices?\n");
    if ((status = scanf("%d", &dice)) != 1)
    {
      if (status == EOF)
        break;
      else
      {
        printf("you should enter an integer.");
        printf("Let's begin again.\n");
        while (getchar() != '\n')
          continue;
        printf("How many sides? Enter 0 to quit.\n");
        continue;
      }
    }
    roll = roll_n_dice(dice, sides);
    printf("You have rolled a %d using %d %d-sides dice.\n", roll, dice, sides);
    printf("How many sides? Enter 0 to quit.\n");
  }
  printf("The rollem function was called %d times.\n", roll_count);

  printf("GOOD FPRTUNE TO YOU!\n");

  getchar();
  getchar();

  return 0;
}