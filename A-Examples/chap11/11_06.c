#include <stdio.h>

#define STLENGTH 5

int main(void)
{
  char words[STLENGTH];

  puts("Enter a string, please.");
  gets(words);
  printf("Your string twice:\n");
  printf("%s\n", words);
  puts(words);
  puts("Done!");
  return 0;
}