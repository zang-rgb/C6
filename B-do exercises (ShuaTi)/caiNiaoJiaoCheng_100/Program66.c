/*
题目：输入3个数a,b,c，按大小顺序输出。

程序分析：利用指针方法。
*/

#include <stdio.h>
void swap(int *m1, int *m2);

int main(void)
{
    int a, b, c;
    int *p1, *p2, *p3;
    printf("Enter:");
    scanf("%d %d %d", &a, &b, &c);
    p1 = &a;
    p2 = &b;
    p3 = &c;
    if (a > b)
        swap(p1, p2);
    if (a > c)
        swap(p1, p3);
    if (b > c)
        swap(p2, p3);
    printf("%d %d %d\n", a, b, c);
    return 0;
}

void swap(int *m1, int *m2)
{
    int t;
    t = *m1;
    *m1 = *m2;
    *m2 = t;
}