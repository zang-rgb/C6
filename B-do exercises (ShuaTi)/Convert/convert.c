#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STACK_INIT_SIZE 100    /*�洢�ռ��ʼ������*/
#define STACKINCREMENT 10    /*�洢�ռ��������*/

typedef struct {
  char * top;
  char * base;
  int stacksize;
} SpStack;

void initStack(SpStack * s)   /*����һ���յ��ڴ�ռ�*/
{
  s->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
  if (s->base == NULL)  
    {
      perror("InitContact::malloc");
      return;
    }
  memset(s->base, 0, STACK_INIT_SIZE * sizeof(char));   //�ڴ濪�ٳɹ���������ڴ�������ֽڳ�ʼ��Ϊ0
  s->top = s-> base;
  s->stacksize = STACK_INIT_SIZE;
}

void push(SpStack * s, int e)
{
  *(s->top) = e;    /*�ڸ��ڴ�ռ䶥������һ��Ԫ��*/
  printf("%d", e);
  s->top++;         /*����һ��Ԫ�غ�ָ���1*/
}

void pop(SpStack * s)
{
  while (s->top != s->base)   /*�����ڴ�ռ䲻Ϊ��ʱ������ڴ�ռ��е�Ԫ��*/
  {    
    s->top --;    /*�Ƚ�ָ���1�ڳ����*/
    printf("%d", *(s->top));
  }
}

void Convert(SpStack * s, int data)
{
  int i, j;
  j = data % 2;
  i = data / 2;
  printf("��ջ����Ϊ��");  /*�����ڴ�ռ��Ϊջ*/
  push(s, j);
  while (i != 0)
  {
    j = i % 2;  // j ��ǰ��
    i = i / 2;  // i �ں���
    push(s, j);
  }
  putchar('\n');
  printf("��ջ����Ϊ������Ӧ�Ķ�������Ϊ����");   /*�����ڴ�ռ��Ϊջ*/
  pop(s);
}

void freeStack(SpStack * s)   /*�ͷ��ڴ�ռ�*/
{
  free(s->base);
}



int main(void)
{
  SpStack s;
  int number;

  printf("����Ҫת��������(q to quit):");
  while(scanf("%d", &number))
  {
    initStack(&s);
    Convert(&s, number);
    putchar('\n');
    printf("����Ҫת��������(q to quit)��");
    freeStack(&s);
  }
  return 0;
}