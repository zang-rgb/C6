/*
题目：某个公司采用公用电话传递数据，数据是整数，在传递过程中是加密的，加密规则如下： 每位数字都加上5,然后用和除以10的余数代替该数字，再将第一位和最后一位交换，第二位和倒数第二位位交换，以此类推
*/

#include <stdio.h>
#define MAX 1000

int main(void)
{
    // 输入原始数据
    int digit;
    int rawNum;
    printf("Enter digit:");
    scanf("%d", &digit);
    printf("Enter rawNum:");
    scanf("%d", &rawNum);
    int arrayNum[MAX];
    for (int i = digit - 1; i >= 0; i--)
    {
        arrayNum[i] = rawNum % 10;
        rawNum /= 10;
    }
    printf("\nrawNum: ");
    for (int i = 0; i < digit; i++)
        printf("%d", arrayNum[i]);
    // 执行加密
    for (int i = 0; i < digit; i++)
    {
        arrayNum[i] += 5;
        arrayNum[i] %= 10;
    }
    for (int i = 0; i < (digit - 1) / 2; i++) // 数组中将第一位和最后一位交换，第二位和倒数第二位位交换，以此类推
                                              // i = 0开始，判断条件是i < (digit - 1) / 2，注意(digit - 1)
    {
        int temp;
        temp = arrayNum[i];
        arrayNum[i] = arrayNum[digit - 1 - i];
        arrayNum[digit - 1 - i] = temp;
    }
    // 加密完成，输出加密数据
    printf("\nencrypt: ");
    for (int i = 0; i < digit; i++)
        printf("%d", arrayNum[i]);
    return 0;
}