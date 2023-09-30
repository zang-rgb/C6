/*
题目：删除一个字符串中的指定字母，如：字符串 "aca"，删除其中的 a 字母。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *deleteCharacters(char *str, char *charSet);

int main(void)
{
    char s[2] = "ab";
    char s2[5] = "abcde";
    printf("%s", deleteCharacters(s2, s));
    return 0;
}

char *deleteCharacters(char *str, char *charSet)
{
    int hash[256];

    if (str == NULL)
        return str;
    for (int i = 0; i < 256; i++)
        hash[i] = 0;

    for (int i = 0; i < strlen(charSet); i++)
        hash[charSet[i]] = 1;

    int currentIndex = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (hash[str[i]] == 0)
            str[currentIndex++] = str[i];
    }
    str[currentIndex] = '\0';

    return str;
}