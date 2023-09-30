/*
题目：一个偶数总能表示为两个素数之和。

素数一般指质数。质数是指在大于1的自然数中，除了1和它本身以外不再有其他因数的自然数.
*/

#include <stdio.h>
#include <math.h>

int IsPrime(int n);
void divide_even(int even, int *m, int *n);

int main(void)
{
    printf("Enter:");
    int num;
    scanf("%d", &num);
    int a, b;
    divide_even(num, &a, &b);
    printf("%d = %d + %d", num, a, b);

    return 0;
}

int IsPrime(int n)
{
    int i;
    if (n == 1)
        return 0;
    for (i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;
    return 1;
}

void divide_even(int even, int *m, int *n)
{
    int i;
    for (i = 2; i < even; i++)
        if (IsPrime(i) && IsPrime(even - i))
            break;
    *m = i;
    *n = even - i;
}
