#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
 
 
#define NAME_MAX 20		//��������������С
#define SEX_MAX 6		//����Ա�������С
#define TELE_MAX 12		//��ŵ绰�������С
#define ADDRESS_MAX 20	//��ŵ�ַ�������С
#define DATA_MAX 1000	//��Ÿ�����Ϣ�������С
#define CAPACITY 3
 
enum c
{
	EXIT,    //0
	ADD,     //1
	DEL,     //2
	SEARCH,  //3
	MOD,     //4
	PRINT,   //5
	SORT,    //6
	EMPTY,   //7
};
 
typedef struct peoInfo
{
	char name[NAME_MAX];
	int age;
	char sex[SEX_MAX];
	char tele[TELE_MAX];
	char address[ADDRESS_MAX];
}peoInfo;
 
/*
//��̬ͨѶ¼
typedef struct contact
{
  //��data����Ϊһ���ں�DATA_MAX��Ԫ�ص����飬�ڴ��С����̶��������ÿ��Ԫ�ض���һ��peoInfo�Ľṹ����
	peoInfo data[DATA_MAX];//��Ÿ�����Ϣ
	int sz;//��¼�м����˵���Ϣ
}contact;
*/

//��̬ͨѶ¼
typedef struct contact
{
	peoInfo * data;//��Ÿ�����Ϣ
	int sz;//��¼�м����˵���Ϣ
  int capacity; //��¼��ǰͨѶ¼�������
}contact;
 
//��ʼ��ͨѶ¼����̬/��̬��
void InitContact(contact* pc);
//������Ϣ
void AddContact(contact* pc);
//��ӡͨѶ¼
void PrintContact(contact* pc);
//ɾ����ϵ��
void DelContact(contact* pc);
//������ϵ��
void SearchContact(contact* pc);
//�޸���ϵ��
void ModContact(contact* pc);
//�����ϵ�ˣ����ͷ��ڴ�ռ�
void EmptyContact(contact* pc);
//��ϵ������
void SortContact(contact* pc);
//�˳������ͷ��ڴ�
void DestroyContact(contact * pc);

