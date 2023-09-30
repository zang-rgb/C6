#include <stdio.h>
int glFun(int a);  
 
void main()   
{
  typedef int (*p)(int);   
  p pFun;  
  pFun = glFun;          //由于pf指向glFun函数
  int aa = (*pFun)(2);   //那么*pf就相当于glFun函数
  printf("%d", aa);
} 

int glFun(int a)
{ 
  return a;
}