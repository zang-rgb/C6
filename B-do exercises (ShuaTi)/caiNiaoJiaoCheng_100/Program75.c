/*
题目：输入一个整数，并将其反转后输出。
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    int num, k;
    int now = 0;
    int a[k], i; // 将每一位存到数组里面
    printf("Enter digits:");
    scanf("%d", &k); // 整数位数
    printf("Enter num:");
    scanf("%d", &num); // 整数

    for (i = 0; i < k; i++) // 使用i之前赋初值就可以了
    {
        a[i] = num % 10; // 存储到数组的顺序是从个位开始，然后是十位百位千位...
        num /= 10;
    }
    for (i = 0; i < k; i++)
        now += a[i] * pow(10, k - i - 1);
    printf("%d", now);

    return 0;
}