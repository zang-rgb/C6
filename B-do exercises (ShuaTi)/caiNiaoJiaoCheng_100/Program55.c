/*
��Ŀ��ѧϰʹ�ð�λȡ��~��
      ֪��������þ��У�����ɳ�����㡣
���������~0=-1; ~1=-2;
*/

#include <stdio.h>
int main(void)
{
    int a, b;
    a = 154;
    printf("%d\n", a);
    b = ~a;
    printf("a �İ�λȡ��ֵΪ��ʮ���ƣ� %d \n", b);
    a = ~a;
    printf("a �İ�λȡ��ֵΪ��ʮ�����ƣ� %x \n", a);
    return 0;
}