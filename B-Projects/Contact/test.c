#include "contact.h"
#include <stdio.h>

/*之所以使用韩函数原型，是为了让编译器在第一次执行到该函数之前就知道如何使用它。
因此，把整个函数定义放在第一次调用该函数之前，也有同样的效果。此时，函数定义也相当于函数原型。
对于较小的函数，这种用法很普遍。*/
void menu() 
{
	printf("-------------------------------\n");
	printf("-------1.add     2.del---------\n");
	printf("-------------------------------\n");
	printf("-------3.search  4.mod---------\n");
	printf("-------------------------------\n");
	printf("-------5.print   6.sort--------\n");
	printf("-------------------------------\n");
	printf("-------7.empty   0.exit--------\n");
	printf("-------------------------------\n");
}

void test()
{
	int input;
	contact con;

	InitContact(&con);

	do {
		menu();
    printf("选择功能:\n");
    scanf("%d", &input);
		switch (input) {
			case EXIT:
				//退出程序
        DestroyContact(&con);
				printf("退出程序。\n");
				break;
			case ADD:
				//增加联系人
				AddContact(&con);
				break;
			case DEL:
				//删除联系人
				DelContact(&con);
				break;
			case SEARCH:
				//查找联系人
				SearchContact(&con);
				break;
			case MOD:
				//修改联系人
				ModContact(&con);
				break;
			case PRINT:
				//打印通讯录
				PrintContact(&con);
				break;
			case SORT:
				//联系人排序
				SortContact(&con);
				break;
			case EMPTY:
				//清空通讯录
				EmptyContact(&con);
				break;
			default:
				//输入错误
				printf("输入的数字无效，请重新选择。\n");
				break;
		}
	}while (input);

}


int main(void)
{
	test();
	return  0;
}