#include <stdio.h>
int main(void)
{
  char firstname[40];
  char lastname[40];

  printf("Please enter your first name.\n");
  scanf("%s", firstname);
  printf("Please enter your last name.\n");
  scanf("%s", lastname);

  printf("%s,%s", lastname, firstname);
  return 0;

}