//func_ptr.c -- 使用函数指针
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LEN 81

char *s_gets(char *st, int n);
char showmenu(void);
char eatline(void);
void show(void (*fp)(char *), char *str);
void ToUpper(char *);
void ToLower(char *);
void Transpose(char *);
void Dummy(char *);

int main(void)
{
  char line[LEN];
  char copy[LEN];
  char choice;
  void (*pfun)(char *);
  puts("Enter a string(empty line to quit):");
  while (s_gets(line, LEN) != NULL && line[0] != '\0')
  {
    while ((choice = showmenu()) != 'n')        //在while循环判断条件中限制了choice不是n，才能进入循环。 
    {
      switch (choice)
      {
      case 'u':
        pfun = ToUpper;
        break;
      case 'l':
        pfun = ToLower;
        break;
      case 't':
        pfun = Transpose;
        break;
      case 'o':
        pfun = Dummy;
        break;
      default:
        break;
      }
      strcpy(copy, line);
      show(pfun, copy);
    }
    puts("Enter a string(empty line to quit):");
  }
  printf("Bye!\n")
  return 0;
}


//模块分解，分而治之
//自顶向下，逐步求精
char *s_gets(char *st, int n)
{
  char * ret_val;
  char * find;
  ret_val = fgets(st, n, stdin);
  if (ret_val)
  {
    find = strchr(st, '\n');
    if (find)
      *find = '\0';
    else 
    {
      while (getchar() != '\n')
        continue;
    }
  }
  return ret_val;
}


char showmenu(void)
{
  char ans;
  puts("Enter menu choice:");
  puts("u) uppercase           l) lowercase");
  puts("t) transposedcase      o) originalcase");
  puts("n) next string");
  ans = getchar();
  ans = tolower(ans);
  eatline();
  while (strchr("ulton", ans) == NULL)
  {
    printf("Please enter u l t o n:\n");
    ans = getchar();
    ans = tolower(ans);
    eatline();
  }
  return ans;
}


char eatline(void)
{
  while (getchar() != '\n')
    continue;
}


void show(void (*fp)(char *), char *str)
{
  (*fp)(str);   //等价于fp(str);
  printf("%s\n", str);
}


void ToUpper(char *str)
{
  while (*str)
  {
    *str = toupper(*str);
    str++;    
  }
}


void ToLower(char *str)
{
  while (*str)
  {
    *str = tolower(*str);
    str++;
  } 
}


void Transpose(char *str)
{
  while (*str)
  {
    if(isupper(*str))
      *str = tolower(*str);
    else if(islower(*str))
      *str = toupper(*str);
    str++;
  }
}


void Dummy(char *str)
{
  //不更改字符串
}