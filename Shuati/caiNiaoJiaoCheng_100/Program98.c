/*
题目：将字符串的小写字母全部转换成大写字母，然后输出到磁盘文件"test98"中保存。 输入的字符串以！结束。
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char str[100] = "abCDef";
    // 将字符串的小写字母全部转换成大写字母
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = toupper(str[i]);
    printf("%s", str);
    // 输出到磁盘文件"test98"中保存
    FILE *fp;
    fp = fopen("test98", "w");
    if (fp == NULL)
    {
        printf("Can't open");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; str[i] != '\0'; i++)
        putc(str[i], fp);
    // 输入的字符串以！结束。
    putc('!', fp);
    return 0;
}