/*
��Ŀ������һ�������������䷴ת�������
*/

#include <stdio.h>
int main()
{
    int n, reversedNumber = 0, remainder;

    printf("����һ������: ");
    scanf("%d", &n);

    while (n != 0)
    {
        remainder = n % 10;
        reversedNumber = reversedNumber * 10 + remainder;
        n /= 10;
    }

    printf("��ת�������: %d", reversedNumber);

    return 0;
}
