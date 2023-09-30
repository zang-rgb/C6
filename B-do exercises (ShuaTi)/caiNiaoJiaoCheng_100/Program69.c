/*
题目：有n个人围成一圈，顺序排号。从第一个人开始报数（从1到3报数），凡报到3的人退出圈子，问最后留下的是原来第几号的那位。
*/

#include <stdio.h>
#define FLAG -100

int main(void)
{
    int num[50];
    int n, i, m, k;
    printf("Enter n: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        num[i] = i + 1; // 给这些人编号1~n

    i = 0;             // i为数组元素的下标，num[i]为这些人的编号
    m = 0;             // m记录退出圈子的人数
    k = 0;             // k报数1,2,3
    while (m <= n - 2) // 至少要剩下两个人进行报数，因为如果只剩下一个人自己喊1，2, 3，那么他自己喊道3也就退出了，将不会有输出
    {
        if (num[i] != FLAG) // 这里关注num[i]的值也就是这个人的编号，不关注下标i了。
                            // 如果这个人的编号不是FLAG才能报数，k++
            k++;
        if (k == 3)
        {
            k = 0;
            m++;           // 报一次3，m++
            num[i] = FLAG; // 报数为3的人编号重置为FLAG，后面这个人就不再进行报数了
        }
        if (i == n - 1) // 如果此时i==n-1，将i赋值为i-1，那么执行i++后i变为0，即可实现回起始位置。再次进行遍历。
            i = -1;
        i++;
    }

    for (i = 0; i < n; i++)
        if (num[i] != FLAG)
            printf("Left : %d", num[i]);

    return 0;
}