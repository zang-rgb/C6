/*
题目：有五个学生，每个学生有3门课的成绩（包括学生号，姓名，三门课成绩），计算出平均成绩，原有的数据和计算出的平均分数存放在磁盘文件"stud"中.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct student
{
    int ID;
    char name[100];
    int C;
    int math;
    int English;
    int average;
} Stu;

int main(void)
{
    FILE *fp;
    Stu xiaoming = {11, "xiaoming", 60, 70, 80}; // average未初始化，自动初始化为0
    Stu xiaofang = {22, "xiaofang", 60, 90, 80, 0};
    Stu xiaohong = {33, "xiaohong", 81, 82, 80, 0};

    xiaoming.average = (xiaoming.C + xiaoming.math + xiaoming.English) / 3;
    xiaofang.average = (xiaofang.C + xiaofang.math + xiaofang.English) / 3;
    xiaohong.average = (xiaohong.C + xiaohong.math + xiaohong.English) / 3;

    Stu s[5];
    s[0] = xiaoming; // 一个结构体可以直接赋值给另一个同类型的结构体，即使成员是数组，也能完成赋值
    s[1] = xiaofang; // 数组不能直接赋值给另一个数组
    s[2] = xiaohong;
    fp = fopen("test100.txt", "w");
    if (fp == NULL)
    {
        printf("Can't open Program99c.txt");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 3; i++)
        fprintf(fp, "%d %s %d %d %d %d\n", s[i].ID, s[i].name, s[i].math, s[i].English,
                s[i].C, s[i].average);
    return 0;
}