/*
打印字符串数组
*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    const char *s[] = {"man", "woman", "girl", "boy", "sister"};
    int k;
    for (k = 0; k < 5; k++)
    {
        printf("%s\n", s[k]);
    }
    return 0;
}