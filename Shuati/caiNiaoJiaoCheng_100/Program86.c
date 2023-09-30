/*
两个字符串拼接
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    char a[100] = "abc";
    char b[100] = "def";
    strcat(a, b);
    puts(a);
    return 0;
}