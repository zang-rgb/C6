/*
题目：猜谜游戏。
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
            printf("猜中了，使用了 %d 次！\n", count);
            if (count == 1)
            {
                printf("你是神级人物了！膜拜\n");
                printf("你已经达到最高级别,还需要玩吗?Y/N \n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y') // 重复玩的一个嵌套循环，打印New Game!等玩家提示信息。
                    caizi();                      // 也可以使用cintinue，但不会打印New Game!等玩家提示信息。
                else
                    printf("谢谢，再见!\n");
            }
            else if (count <= 5)
            {
                printf("你是王级人物了！非常赞\n");
                printf("需要挑战最高级别不?Y/N \n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y')
                    caizi();
                else
                    printf("谢谢，再见!\n");
            }
            else if (count <= 10)
            {
                printf("你是大师级人物了！狂赞\n");
                printf("需要挑战最高级别不?Y/N \n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y')
                    caizi();
                else
                    printf("谢谢，再见!\n");
            }
            else if (count <= 15)
            {
                printf("你是钻石级人物了！怒赞\n");
                printf("需要挑战最高级别不?Y/N \n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y')
                    caizi();
                else
                    printf("谢谢，再见!\n");
            }
            else
            {
                printf("猜测次数超过15次, 重玩? Y/N\n");
                getchar();
                scanf("%c", &again);
                if (again == 'Y' || again == 'y')
                    caizi();
                else
                    printf("谢谢，再见!\n");
            }
            break;
        }
        else if (guessNum < randNum)
            puts("Too Small. Enter again: ");
        else
            puts("Too Big. Enter again: ");
    }
}