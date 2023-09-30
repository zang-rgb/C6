#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STACK_INIT_SIZE 100    /*存储空间初始分配量*/
#define STACKINCREMENT 10    /*存储空间分配增量*/

typedef struct {
  char * top;
  char * base;
  int stacksize;
} SpStack;

void initStack(SpStack * s)   /*分配一个空的内存空间*/
{
  s->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
  if (s->base == NULL)  
    {
      perror("InitContact::malloc");
      return;
    }
  memset(s->base, 0, STACK_INIT_SIZE * sizeof(char));   //内存开辟成功，将这块内存的所有字节初始化为0
  s->top = s-> base;
  s->stacksize = STACK_INIT_SIZE;
}

void push(SpStack * s, int e)
{
  *(s->top) = e;    /*在该内存空间顶部插入一个元素*/
  printf("%d", e);
  s->top++;         /*插入一个元素后，指针加1*/
}

void pop(SpStack * s)
{
  while (s->top != s->base)   /*当该内存空间不为空时，输出内存空间中的元素*/
  {    
    s->top --;    /*先将指针减1在出输出*/
    printf("%d", *(s->top));
  }
}

void Convert(SpStack * s, int data)
{
  int i, j;
  j = data % 2;
  i = data / 2;
  printf("入栈数字为：");  /*将该内存空间称为栈*/
  push(s, j);
  while (i != 0)
  {
    j = i % 2;  // j 在前面
    i = i / 2;  // i 在后面
    push(s, j);
  }
  putchar('\n');
  printf("出栈数字为（即对应的二进制数为）：");   /*将该内存空间称为栈*/
  pop(s);
}

void freeStack(SpStack * s)   /*释放内存空间*/
{
  free(s->base);
}



int main(void)
{
  SpStack s;
  int number;

  printf("输入要转换的数字(q to quit):");
  while(scanf("%d", &number))
  {
    initStack(&s);
    Convert(&s, number);
    putchar('\n');
    printf("输入要转换的数字(q to quit)：");
    freeStack(&s);
  }
  return 0;
}