/*
题目：读取7个整数，每读取一个整数，程序打印出该整数个数的 ＊。
整数大小0-50
*/

#include <stdio.h>
#include <stdlib.h>

void Printff(int x)
{
    for (int i = 0; i < x; i++)
        printf("*");
}

int main(void)
{
    int num;

    for (int i = 0; i < 7; i++)
    {
        printf("Enter:");
        scanf("%d", &num);
        if (num < 0 || num > 50)
        {
            printf("Again ");
            i--;
            continue;
        }
        else
            Printff(num);
        printf("\n");
    }

    return 0;
}