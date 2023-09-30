/*
题目：学习使用register定义变量的方法。
*/

#include <stdio.h>

int main(void)
{
    register int i;
    int sum;
    for (i = 1; i <= 100; i++)
        sum += i;
    printf("sum = %d\n", sum);

    return 0;
}