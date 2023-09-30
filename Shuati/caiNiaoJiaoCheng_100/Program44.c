/*
题目：学习使用如何调用外部函数。
*/

#include <stdio.h>

int a, b, c;
void add(void)
{
    int a = 3;
    c = a + b;
}

int main(void)
{
    a = 4;
    b = 4;
    add();
    printf("c = %d\n", c);
    return 0;
}