#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
 
 
#define NAME_MAX 20		//存放姓名的数组大小
#define SEX_MAX 6		//存放性别的数组大小
#define TELE_MAX 12		//存放电话的数组大小
#define ADDRESS_MAX 20	//存放地址的数组大小
#define DATA_MAX 1000	//存放个人信息的数组大小
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
//静态通讯录
typedef struct contact
{
  //把data声明为一个内含DATA_MAX个元素的数组，内存大小分配固定。数组的每个元素都是一个peoInfo的结构变量
	peoInfo data[DATA_MAX];//存放个人信息
	int sz;//记录有几个人的信息
}contact;
*/

//动态通讯录
typedef struct contact
{
	peoInfo * data;//存放个人信息
	int sz;//记录有几个人的信息
  int capacity; //记录当前通讯录最大容量
}contact;
 
//初始化通讯录（静态/动态）
void InitContact(contact* pc);
//增加信息
void AddContact(contact* pc);
//打印通讯录
void PrintContact(contact* pc);
//删除联系人
void DelContact(contact* pc);
//查找联系人
void SearchContact(contact* pc);
//修改联系人
void ModContact(contact* pc);
//清空联系人，并释放内存空间
void EmptyContact(contact* pc);
//联系人排序
void SortContact(contact* pc);
//退出，并释放内存
void DestroyContact(contact * pc);

