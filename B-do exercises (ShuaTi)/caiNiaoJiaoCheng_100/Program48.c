/*
��Ŀ����#define������ϰ3��
*/

#define LAG >
#define SMA <
#define EQ ==
#include <stdio.h>
int main(void)
{
    int i, j;
    printf("�������������֣�\n");
    scanf("%d %d", &i, &j);
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