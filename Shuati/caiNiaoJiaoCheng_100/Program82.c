/*
题目：八进制转换为十进制
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void)
{
    char s[20];
    int n = 0;
    int k;
    printf("Enter:");
    scanf("%s", s);
    for (int i = strlen(s) - 1, k = 0; i >= 0; i--, k++)
        n += (s[i] - '0') * pow(8, k);

    printf("%d", n);

    return 0;
}