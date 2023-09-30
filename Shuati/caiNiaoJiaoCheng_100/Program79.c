/*
题目：字符串排序。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char *s1, char *s2);

int main(void)
{
    char s1[20] = "hello";
    char s2[20] = "abc";
    char s3[20] = "def";
    if (strcmp(s1, s2) > 0)
        swap(s1, s2);
    if (strcmp(s1, s3) > 0)
        swap(s1, s3);
    if (strcmp(s2, s3) > 0)
        swap(s2, s3);
    printf("%s\n%s\n%s", s1, s2, s3);
    return 0;
}

void swap(char *s1, char *s2)
{
    char temp[20];
    strcpy(temp, s1);
    strcpy(s1, s2);
    strcpy(s2, temp);
}