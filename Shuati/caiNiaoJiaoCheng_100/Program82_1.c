/*
题目：八进制转换为十进制
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void)
{
    int num;
    printf("Enter:");
    scanf("%d", &num);
    int sum = 0;
    int i = 0;
    while (num != 0)
    {
        sum += (num % 10) * pow(8, i++);
        num /= 10;
    }
    printf("%d", sum);

    return 0;
}