/*
��Ŀ��������Ϸ��
*/

#include <stdio.h>
#include <stdlib.h>
void caizi(void);

int main(void)
{
    caizi();
    return 0;
}

void caizi(void)
{
    int randNum = (rand() % 100) + 1;
    int guessNum;
    int count = 0;
    char again;
    printf("New Game!\n");
    printf("This is a Program with a randNum. Now Please Enter your guessNum.\n");
    while (1)
    {
        printf("Enter: ");
        scanf("%d", &guessNum);
        count++;
        if (guessNum == randNum)
        {
            printf("�����ˣ�ʹ���� %d �Σ�\n", count);
            if (count == 1)
            {
                printf("�����������ˣ�Ĥ��\n");
                printf("���Ѿ��ﵽ��߼���,����Ҫ����?Y/N \n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y') // �ظ����һ��Ƕ��ѭ������ӡNew Game!�������ʾ��Ϣ��
                    caizi();                      // Ҳ����ʹ��cintinue���������ӡNew Game!�������ʾ��Ϣ��
                else
                    printf("лл���ټ�!\n");
            }
            else if (count <= 5)
            {
                printf("�������������ˣ��ǳ���\n");
                printf("��Ҫ��ս��߼���?Y/N \n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y')
                    caizi();
                else
                    printf("лл���ټ�!\n");
            }
            else if (count <= 10)
            {
                printf("���Ǵ�ʦ�������ˣ�����\n");
                printf("��Ҫ��ս��߼���?Y/N \n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y')
                    caizi();
                else
                    printf("лл���ټ�!\n");
            }
            else if (count <= 15)
            {
                printf("������ʯ�������ˣ�ŭ��\n");
                printf("��Ҫ��ս��߼���?Y/N \n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y')
                    caizi();
                else
                    printf("лл���ټ�!\n");
            }
            else
            {
                printf("�²��������15��, ����? Y/N\n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y')
                    caizi();
                else
                    printf("лл���ټ�!\n");
            }
            break;
        }
        else if (guessNum < randNum)
            puts("Too Small. Enter again: ");
        else
            puts("Too Big. Enter again: ");
    }
}