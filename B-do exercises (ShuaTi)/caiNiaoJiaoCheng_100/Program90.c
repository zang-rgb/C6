/*
数组元素对调，将第一位和最后一位交换，第二位和倒数第二位位交换，以此类推
*/

#include <stdio.h>

#define M 5
int main()
{
    int a[M] = {1, 2, 3, 4, 5};
    int i;
    for (i = 0; i < (M - 1) / 2; i++)
    {
        int temp;
        temp = *(a + i);
        *(a + i) = *(a + M - 1 - i);
        *(a + M - 1 - i) = temp;
    }
    for (i = 0; i < M; i++)
    {
        printf("%d\t", *(a + i));
    }
}