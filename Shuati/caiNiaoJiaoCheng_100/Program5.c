/*
题目：输入三个整数x,y,z，请把这三个数由小到大输出
分析：
依次两两对比，交换位置，用的是冒泡法的思路。
*/

#include <stdio.h>

int main(void)
{
    int arr[3];
    int i, j, len;
    int t = 0;

    printf("请输入三个整数,以空格隔开,最后点击enter键结束\r\n");
    scanf("%d", &arr[0]);
    scanf("%d", &arr[1]);
    scanf("%d", &arr[2]);

    len = (int)sizeof(arr) / sizeof(arr[0]); // 获取数组长度  这里完全没必要这样做，只是好奇怎么获取c的数组长度
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (arr[i] > arr[j])
            {
                t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
    printf("由小到大为：\n");
    for (i = 0; i < len; i++)
        printf("%d  ", arr[i]);
    return 0;
}
