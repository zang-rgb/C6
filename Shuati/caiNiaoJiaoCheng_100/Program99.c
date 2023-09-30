/*
题目：有两个磁盘文件A和B,各存放一行字母，要求把这两个文件中的信息合并（按字母顺序排列），输出到一个新文件C中。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    FILE *fpa, *fpb, *fpc;
    int i, j, k;
    char temp;
    char stra[100], strb[100];
    // 以读方式打开A, B文件
    fpa = fopen("Program99A.txt", "r");
    fpb = fopen("Program99B.txt", "r");
    // 文件需要存在，需要可以正常打开
    if (fpa == NULL)
    {
        printf("Can't open Program99A.txt");
        exit(EXIT_FAILURE);
    }
    if (fpb == NULL)
    {
        printf("Can't open Program99B.txt");
        exit(EXIT_FAILURE);
    }
    fpc = fopen("Program99C.txt", "w");
    if (fpc == NULL)
    {
        printf("Can't open Program99c.txt");
        exit(EXIT_FAILURE);
    }
    // 读取A, B文件内容
    fgets(stra, 100, fpa);
    fgets(strb, 100, fpb);
    fclose(fpa);
    fclose(fpb);
    // 合并A, B文件内容
    strcat(stra, strb);
    printf("%s", stra);
    // 冒泡排序
    for (i = 0; i < strlen(stra) - 1; i++) //-1是因为不用与自己比较，所以比的数就少一个
    {
        int FLAG = 0;
        for (j = 0; j < strlen(stra) - 1 - i; j++) // strlen(stra) - 1是常规数组下标取值范围（因为有j+1），再- i是因为每一趟就会少一个数比较
        {
            if (stra[j] > stra[j + 1])
            {
                temp = stra[j + 1];
                stra[j + 1] = stra[j];
                stra[j] = temp;
                FLAG = 1
            }
        }
        if (FLAG == 0) // 如果某一趟没有交换位置，则说明已经排好序，排序结束，直接退出外层for循环
            break;
    }

    // 输出到C文件
    fputs(stra, fpc);
    printf("\n%s", stra);
    fclose(fpc);
    return 0;
}