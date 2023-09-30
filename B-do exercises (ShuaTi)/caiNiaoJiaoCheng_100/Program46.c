/*
题目：宏#define命令练习1。
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define SQ(x) (x) * (x)

int main(void)
{
    int num;
    int again = TRUE;
    printf("如果值小于50程序终止");
    while (again)
    {
        printf("\nEnter num:");
        scanf("%d", &num);
        printf("\nSQ() = %d", SQ(num));
        if (num >= 50)
            again = TRUE;
        else
            again = FALSE;
    }

    return 0;
}