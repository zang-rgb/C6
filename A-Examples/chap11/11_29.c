/*读入字符串，并排序字符串*/
#include <stdio.h>
#include <string.h>
#define SIZE 81
#define LIM 20
#define HALT ""
char * s_gets(char * st, int n);
void stsrt(char * string[], int num);

int main(void)
{
  char input[LIM][SIZE];
  char* psstr[LIM];
  int ct = 0;
  int k;
  printf("Input up to %d lines, and I will sort them.\n", LIM);
  printf("To stop, press the Enter key at a line's start.\n");
  while (ct < LIM && s_gets(input[ct], SIZE) != NULL && input[ct][0] != '\0')
  {
    psstr[ct] = input[ct];
    ct++;
  }
  stsrt(psstr, ct);
  puts("\nHere's the sorted list:\n");
  for (k = 0; k < ct; k++)
    puts(psstr[k]);

  return 0;
}

char * s_gets(char * st, int n)
{
  char * ret_val;
  int i = 0;

  ret_val = fgets(st, n, stdin);
  if (ret_val)
  {
    while (st[i] != '\n' && st[i] != '\0')
      i++;
    if (st[i] == '\n')
      st[i] ='\0';
    else
      while(getchar() != '\n')
        continue;
  }

  return ret_val;
}


void stsrt(char * string[], int num)
{
  char  * temp;
  int top, seek;

  for (top = 0; top < num - 1; top++)
    for (seek = top + 1; seek < num; seek++)
        if (strcmp(string[top], string[seek]) > 0)
        {
          temp = string[top];
          string[top] = string[seek];
          string[seek] = temp;
        }
}