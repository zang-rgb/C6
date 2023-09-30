/*
题目：写一个函数，求一个字符串的长度，在 main 函数中输入字符串，并输出其长度。
*/

#include <stdio.h>
int length(const char *s);

int main(void)
{
    const char *s = "helloworld";
    printf("%d", length(s));
    return 0;
}

int length(const char *s)
{
    int len = 0;
    while (*s != '\0')
    {
        printf("%-5c", *s);
        len++;
        s++;
    }
    printf("\n");
    return len;
}