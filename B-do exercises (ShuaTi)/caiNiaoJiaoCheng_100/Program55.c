/*
题目：学习使用按位取反~。
      知道意义会用就行，结果由程序计算。
程序分析：~0=-1; ~1=-2;
*/

#include <stdio.h>
int main(void)
{
    int a, b;
    a = 154;
    printf("%d\n", a);
    b = ~a;
    printf("a 的按位取反值为（十进制） %d \n", b);
    a = ~a;
    printf("a 的按位取反值为（十六进制） %x \n", a);
    return 0;
}