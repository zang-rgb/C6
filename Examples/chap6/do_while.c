//do_while.c -- 出口条件循环
#include <stdio.h>
int main(void)
{
  const int secret_code = 13;
  int code_entered;

  do
  {
    printf("Enter code: ");
    scanf("%d", &code_entered);
  } while (code_entered != secret_code);
  printf("Correct!");

  return 0;
}