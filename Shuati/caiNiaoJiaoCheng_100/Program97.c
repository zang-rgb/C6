/*
题目：从键盘输入一些字符，逐个把它们送到磁盘上去，直到输入一个#为止。
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    char ch;
    if ((fp = fopen("test96", "w")) == NULL)
    {
        printf("error: cannot open file!\n");
        exit(0);
    }
    printf("Enter, End with '#':\n");
    while ((ch = getchar()) != '#')
        putc(ch, fp);
    fclose(fp);
    return 0;
}