#include <stdio.h>

int main(void)
{
    char p[100];
    int i;
    int letters = 0, spaces=0,digits=0,others=0;
    printf("请输入一些字母:");
    scanf("%s", &p[0]);
    for (i = 0; p[i] != '\0'; i++)
    {
         if((p[i]>='a'&&p[i]<='z')||(p[i]>='A'&&p[i]<='Z'))
            letters++;
        else if(p[i]>='0'&&p[i]<='9')
            digits++;
        else if(p[i]==' ')
            spaces++;
        else
            others++;

    }
    printf("字母=%d,数字=%d,空格=%d,其他=%d\n",letters,digits,spaces,others);
    return 0;
}