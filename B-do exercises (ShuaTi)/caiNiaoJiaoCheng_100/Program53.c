/*
��Ŀ��ѧϰʹ�ð�λ��� ^��
      ֪��������þ��У�����ɳ�����㡣
���������0^0=0; 0^1=1; 1^0=1; 1^1=0 ��
*/
#include <stdio.h>
int main(void)
{
    int a, b;
    a = 077;
    b = a ^ 3;
    printf("b ��ֵΪ %d \n", b);
    b ^= 7;
    printf("b ��ֵΪ %d \n", b);
    return 0;
}