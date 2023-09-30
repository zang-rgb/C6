/*
如果要计算或者处理值，那么函数调用传递值。
如果要在被调函数中改变主调函数的变量，那么函数调用传递地址
*/

#include <stdio.h>

typedef struct student
{
    int x;
    char y;
} Stu;

void func(Stu *onestudent)
{
    onestudent->x = 11;
    onestudent->y = 'M';
}

int main(void)
{
    Stu xiaoming;
    xiaoming.x = 10;
    xiaoming.y = 'F';
    func(&xiaoming);
    printf("%d\t%c\t", xiaoming.x, xiaoming.y);
    return 0;
}