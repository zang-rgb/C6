#include <stdio.h>
#include <string.h>
char * s_gets(char * st, int n);
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100 /* maximum number of books */
struct book { /* set up book template */
  char title[MAXTITL];
  char author[MAXAUTL];
  float value;
};
void sortt(struct book * pb[], int n);
void sortv(struct book * pb[], int n);


int main(void)
{
  struct book library[MAXBKS]; /* array of book structures */
  struct book * pbk[MAXBKS]; /* pointers for sorting */
  int count = 0;
  int index;
  printf("Please enter the book title.\n");
  printf("Press [enter] at the start of a line to stop.\n");
  while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL && library[count].title[0] != '\0')
  {
    printf("Now enter the author.\n");
    s_gets(library[count].author, MAXAUTL);
    printf("Now enter the value.\n");
    scanf("%f", &library[count].value);
    pbk[count] = &library[count];
    count++;
    while (getchar() != '\n')
      continue; /* clear input line */
    if (count < MAXBKS)
      printf("Enter the next title.\n");
  }
  printf("Here is the list of your books:\n");
  for (index = 0; index < count; index++)
    printf("%s by %s: $%.2f\n", library[index].title, library[index].author, library[index].value);
  
  printf("Here is the list of your books sorted by title:\n");
  sortt(pbk, count);
  for (index = 0; index < count; index++)
    printf("%s by %s: $%.2f\n", pbk[index]->title, pbk[index]->author, pbk[index]->value);
  sortv(pbk, count);
  printf("Here is the list of your books sorted by value:\n");
  for (index = 0; index < count; index++)
    printf("%s by %s: $%.2f\n", pbk[index]->title, pbk[index]->author, pbk[index]->value);
  return 0;
}
void sortt(struct book * pb[], int n) //pb是指针数组，数组的每个元素都是指针，指向struct book类型的结构体
{
  int top, search;
  struct book * temp;           //temp是指针，指向struct book类型的结构体
  for (top = 0; top < n -1; top++)
    for (search = top + 1; search < n; search++)
      if (strcmp(pb[search]->title, pb[top]->title) < 0)
      {
        temp = pb[search];      //指针赋值，即将内存地址的值赋过去，即是直接改变了指针所指向的结构体变量
        pb[search] = pb[top];
        pb[top] = temp;
      } 
}
void sortv(struct book * pb[], int n)
{
  int top, search;
  struct book * temp;
  for (top = 0; top < n -1; top++)
    for (search = top + 1; search < n; search++)
      if (pb[search]->value < pb[top]->value)
      {
        temp = pb[search];
        pb[search] = pb[top];
        pb[top] = temp;
      }
  }

char * s_gets(char * st, int n)
{
  char * ret_val;
  char * find;
  
  ret_val = fgets(st, n, stdin);
  if (ret_val)
  {
    find = strchr(st, '\n'); // look for newline
    if (find) // if the address is not NULL,
      *find = '\0'; // place a null character there
    else
      while (getchar() != '\n')
      continue; // dispose of rest of line
  }
  return ret_val;
}