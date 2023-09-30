/*
题目：编写一个函数，输入n为偶数时，调用函数求1/2+1/4+...+1/n,当输入n为奇数时，调用函数1/1+1/3+...+1/n(利用指针函数)。
*/

#include <stdio.h>
double evennumber(int n);
double oddnumber(int n);

int main(void)
{
    int num;
    printf("Enter:");
    scanf("%d", &num);
    double (*pfun)(int n);
    if (num % 2 == 0)
        pfun = evennumber;
    else
        pfun = oddnumber;
    printf("result : %lf", pfun(num));

    return 0;
}

double evennumber(int n)
{
    double i;
    double evenresult = 0;
    for (i = 2; i <= n; i += 2)
        evenresult += (1 / i);
    return evenresult;
}

double oddnumber(int n)
{
    double i;
    double oddresult = 0;
    for (i = 1; i <= n; i += 2)
        oddresult += (double)(1 / i);
    return oddresult;
}