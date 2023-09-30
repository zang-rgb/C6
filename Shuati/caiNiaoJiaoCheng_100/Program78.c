#include <stdio.h>
#include <stdlib.h>
struct man
{
    char name[20];
    int age;
} person[3] = {"li", 18, "wang", 25, "sun", 22}; // 声明结构体数组并初始化，每个数组成员是一个结构体
/*
struct man{
    char name[20];
    int  age;
}
person[3]={{"li",18},{"wang",25},{"sun",22}};
*/

int main()
{
    struct man *q, *p; // 定义两个结构体指针
    int i, m = 0;
    q = NULL;   // 指针变量是使用前必须初始化，如果没有合适的初始化值，可初始化为NULL
    p = person; // 初始化p为指向结构体数组person的首地址，即为指向第一个结构体
    for (i = 0; i < 3; i++)
    {
        if (m < p->age)
        {
            m = p->age;
            q = p; // q指向最大年龄对应的那个结构体
        }
        p++;
    }
    printf("%s %d\n", q->name, q->age); // 将q输出出来
    return 0;
}