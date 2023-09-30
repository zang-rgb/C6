/*
��Ŀ���� n ��������ʹ��ǰ�����˳������� m ��λ�ã����m���������ǰ��� m ������
�������������ʹ��һ������������������Ҫ�ƶ���Ԫ�أ�Ȼ���ٽ�Ԫ�ذ���Ҫ���ƶ�����ȷ��λ�á�
*/

// ����ԭ����
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
    for (i = n - m, j = 0; i < n - 1, j < m; i++, j++) // i. j��������ͬʱ�������ﵽЧ��
        b[j] = a[i];
}

void printf_f(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%5d", a[i]);
    printf("\n");
}