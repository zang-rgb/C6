/*
题目：学习使用按位与 &。
      知道意义会用就行，结果由程序计算。
程序分析：0&0=0; 0&1=0; 1&0=0; 1&1=1 。
*/
#include <stdio.h>
int main(void)
{
    int a, b;
    a = 077; // 八进制
    b = a & 3;
    printf("a & b(decimal) 为 %d \n", b);
    b &= 7;
    printf("a & b(decimal) 为 %d \n", b);
    return 0;
}