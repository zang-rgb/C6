/*
题目：判断一个素数能被几个9组成的数整除。
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    int num;
    printf("Enter:");
    scanf("%d", &num);
    int i;
    long int k = 9;
    for (i = 1;; i++)
        if (k % num == 0)
            break;
        else
            k += 9 * pow(10, i);
    printf("%ld", k);
    return 0;
}