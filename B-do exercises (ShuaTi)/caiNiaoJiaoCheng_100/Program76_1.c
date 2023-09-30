/*
题目：编写一个函数，输入n为偶数时，调用函数求1/2+1/4+...+1/n,当输入n为奇数时，调用函数1/1+1/3+...+1/n(利用指针函数)。
*/

#include <stdio.h>
typedef double (*EVENODD)(int n); // 使用typedef函数指针
// 定义了一种EVENODD的类型，并定义这种类型为指向某种函数的指针。这种函数以一个int为参数并返回double类型。后面就可以像使用int,char一样使用EVENODD了。
double evennumber(int n);
double oddnumber(int n);

int main(void)
{
    int num;
    printf("Enter:");
    scanf("%d", &num);
    EVENODD pfun; // 这里使用这个新类型EVENODD定义了指针变量pFun，指向这种函数
    // EVENODD pfun1
    // EVENODD pfun2
    if (num % 2 == 0)
        pfun = evennumber; // 给指针变量pfun赋值
    else
        pfun = oddnumber;
    printf("result : %lf", pfun(num)); // 使用函数指针变量pfun
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
