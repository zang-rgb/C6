/*
题目：输入数组，最大的与第一个元素交换，最小的与最后一个元素交换，输出数组。
*/

#include <stdio.h>
void func(int a[], int n);
void printf_f(int a[], int n);

int main(void)
{
    int a[20];
    int n;
    printf("Enter length of array:");
    scanf("%d", &n);
    printf("Enter array:");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    func(a, n);
    printf_f(a, n);
    return 0;
}

void func(int a[], int n)
{
    int max = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > a[0])
        {
            max = a[0];
            a[0] = a[i];
            a[i] = max;
        }
    }
    int min = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] < a[n - 1])
        {
            min = a[n - 1];
            a[n - 1] = a[i];
            a[i] = min;
        }
    }
}

void printf_f(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d\t", a[i]);
    printf("\n");
}