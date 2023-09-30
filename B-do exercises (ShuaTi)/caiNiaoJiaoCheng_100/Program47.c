/*
题目：宏#define命令练习2。
*/

// \ 代表继续符：可用于一行的结尾，表示本行与下一行连接起来

#include <stdio.h>
#define exchange(a, b) \
    {                  \
        int t;         \
        t = a;         \
        a = b;         \
        b = t;         \
    }

int main(void)
{
    int x = 10;
    int y = 20;
    printf("x = %d\ty = %d\n", x, y);
    exchange(x, y);
    printf("x = %d\ty = %d\n", x, y);
    return 0;
}