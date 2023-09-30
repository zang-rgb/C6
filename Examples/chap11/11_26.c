/*使用strcpy()*/
#include <stdio.h>
#include <string.h>
#define SIZE 40
#define WORDS "beast"

int main(void)
{
  const char * orig;
  orig = WORDS;
  char copy[SIZE] = "Be the best that you can be.";
  char * ps;

  puts(orig);
  puts(copy);
  ps = strcpy(copy + 7, orig);
  puts(copy);
  puts(ps);

  return 0;
}