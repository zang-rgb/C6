/*
题目：计算字符串中子串出现的次数 。
*/

#include <stdio.h>
#include <string.h>

int func(char *s1, char *s2);

int main(void)
{
    printf("%d\n", func("dh123dhgfdgsshdhscnbdh", "dh"));
    return 0;
}

int func(char *s1, char *s2)
{
    int count = 0;
    int len_s2 = strlen(s2);
    char *p;
    while ((p = strstr(s1, s2)) != NULL)
    {
        count++;
        s1 = p + len_s2;
    }
    return count;
}