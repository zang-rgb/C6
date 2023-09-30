/*
题目：学习 static 定义静态变量的用法。
*/
#include <stdio.h>
void trystat(void);

int main(void)
{
    int count;
    for (count = 0; count < 3; count++)
        trystat();

    return 0;
}

void trystat(void)
{
    int fade = 1;
    static int stay = 1;

    printf("fade = %d, stay = %d\n", fade++, stay++);
}