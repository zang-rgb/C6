/*
题目：将一个数组逆序输出。
*/

#include <stdio.h>
#define N 10

int main(void)
{
    int a[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 9; i >= 0; i--)
        printf("%d ", a[i]);
    return 0;
}