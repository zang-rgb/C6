/*
��Ŀ��#include ��Ӧ����ϰ��
*/

#include <stdio.h>
#include "Program50test.h"

int main(void)
{
    int i = 10;
    int j = 20;
    if (i LAG j)
        printf("%d ���� %d \n", i, j);
    else if (i EQ j)
        printf("%d ���� %d \n", i, j);
    else if (i SMA j)
        printf("%d С�� %d \n", i, j);
    else
        printf("û��ֵ��\n");
    return 0;
}