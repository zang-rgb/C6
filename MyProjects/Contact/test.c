#include "contact.h"
#include <stdio.h>

/*֮����ʹ�ú�����ԭ�ͣ���Ϊ���ñ������ڵ�һ��ִ�е��ú���֮ǰ��֪�����ʹ������
��ˣ�����������������ڵ�һ�ε��øú���֮ǰ��Ҳ��ͬ����Ч������ʱ����������Ҳ�൱�ں���ԭ�͡�
���ڽ�С�ĺ����������÷����ձ顣*/
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
    printf("ѡ����:\n");
    scanf("%d", &input);
		switch (input) {
			case EXIT:
				//�˳�����
        DestroyContact(&con);
				printf("�˳�����\n");
				break;
			case ADD:
				//������ϵ��
				AddContact(&con);
				break;
			case DEL:
				//ɾ����ϵ��
				DelContact(&con);
				break;
			case SEARCH:
				//������ϵ��
				SearchContact(&con);
				break;
			case MOD:
				//�޸���ϵ��
				ModContact(&con);
				break;
			case PRINT:
				//��ӡͨѶ¼
				PrintContact(&con);
				break;
			case SORT:
				//��ϵ������
				SortContact(&con);
				break;
			case EMPTY:
				//���ͨѶ¼
				EmptyContact(&con);
				break;
			default:
				//�������
				printf("�����������Ч��������ѡ��\n");
				break;
		}
	}while (input);

}


int main(void)
{
	test();
	return  0;
}