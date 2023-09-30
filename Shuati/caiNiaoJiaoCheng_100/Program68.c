/*
题目：有 n 个整数，使其前面各数顺序向后移 m 个位置，最后m个数变成最前面的 m 个数。
程序分析：可以使用一个辅助数组来保存需要移动的元素，然后再将元素按照要求移动到正确的位置。
*/

// 保留原数组
#include <stdio.h>
#define ARRAYNUM 6
#define NUM 2
void modifyArray(int *a, int b[], int n, int m);
void printf_f(int a[], int n);

int main(void)
{
    int a[ARRAYNUM] = {0, 1, 2, 3, 4, 5};
    int b[ARRAYNUM] = {0};
    printf("\nRaw Array:        ");
    printf_f(a, ARRAYNUM);
    modifyArray(a, b, ARRAYNUM, NUM);
    printf("After modifyArray:");
    printf_f(b, ARRAYNUM);
    return 0;
}

void modifyArray(int *a, int b[], int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
        b[i + m] = a[i];
    for (i = n - m, j = 0; i < n - 1, j < m; i++, j++) // i. j两个变量同时进行来达到效果
        b[j] = a[i];
}

void printf_f(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%5d", a[i]);
    printf("\n");
}