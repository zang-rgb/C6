/*
��Ŀ��������������x,y,z���������������С�������
������
���������Աȣ�����λ�ã��õ���ð�ݷ���˼·��
*/

#include <stdio.h>

int main(void)
{
    int arr[3];
    int i, j, len;
    int t = 0;

    printf("��������������,�Կո����,�����enter������\r\n");
    scanf("%d", &arr[0]);
    scanf("%d", &arr[1]);
    scanf("%d", &arr[2]);

    len = (int)sizeof(arr) / sizeof(arr[0]); // ��ȡ���鳤��  ������ȫû��Ҫ��������ֻ�Ǻ�����ô��ȡc�����鳤��
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
    printf("��С����Ϊ��\n");
    for (i = 0; i < len; i++)
        printf("%d  ", arr[i]);
    return 0;
}
