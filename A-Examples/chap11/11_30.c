/*mod_str.c -- 修改字符串*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LIMIT 81
void ToUpper(char *st);
int PunctCount(const char *); //不改变字符串

int main(void)
{
  char line[LIMIT];
  char * find;

  puts("Please enter a line:");
  fgets(line, LIMIT, stdin);
  find = strchr(line, '\n');
  if (find)
    *find = '\0';
  ToUpper(line);
  puts(line);
  printf("%d\n", PunctCount(line));

  return 0;
}

void ToUpper(char *st)
{
  while(*st)
  {
    *st = toupper(*st);
    st++;
  }
}

int PunctCount(const char *st)
{
  int count = 0;
  while(*st)
  {
    if(ispunct(*st))
      count++;
    st++;
  }

  return count;
}