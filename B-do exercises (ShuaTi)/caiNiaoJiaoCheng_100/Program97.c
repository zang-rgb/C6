/*
��Ŀ���Ӽ�������һЩ�ַ�������������͵�������ȥ��ֱ������һ��#Ϊֹ��
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