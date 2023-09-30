/*
题目：简单的结构体应用实例。
*/

#include <stdio.h>

struct programing
{
    float constant;
    char *c;
};

int main(void)
{
    struct programing variable;
    const char *string = "https://www.runoob.com";

    variable.constant = 1.23;
    variable.c = string;

    printf("%f\n", variable.constant);
    printf("%s\n", variable.c);
    return 0;
}