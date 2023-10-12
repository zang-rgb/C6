#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

#define HEADER1 " -------------------------------BOOK TICKET----------------------------------\n"
#define HEADER2 " |  number  |start city|reach city|takeofftime|receivetime|price|ticketnumber|\n"
#define HEADER3 " |----------|----------|----------|-----------|-----------|-----|------------|\n" 
#define FORMAT  "|%-10s|%-10s|%-10s|%-10s |%-10s |%5d|  %5d     |"
#define DATA    p->data.num,p->data.startcity,p->data.reachcity,p->data.takeofftime,p->data.receivetime,p->data.price,p->data.ticketNum
int saveflag = 0;
/*声明存储火车信息的结构体，即结构布局，还未创建结构变量*/
struct train
{
  char num[10];           /*列车号*/
  char startcity[10];     /*出发城市*/
  char reachcity[10];     /*到达城市*/
  char takeofftime[10];   /*发车时间*/
  char receivetime[10];   /*到达时间*/
  int price;              /*票价*/
  int ticketNum;          /*票数*/
};

/*声明存储订票人信息的结构体*/
struct man
{
  char num[10];            /*身份ID*/
  char name[10];          /*姓名*/
  int bookNum;            /*订购票数*/
};

/*定义存储火车信息的链表的节点结构*/
typedef struct node
{
  struct train data;
  struct node * next;
}Node, * Link;

/*
以上代码可以分解为：
typedef struct node Node; //将结构体类型struct node 重命名为Node
typedef struct node * Link; //将struct node * 重命名为Link
*/

/*定义存储订票人信息的链表的节点结构*/
typedef struct Man
{
  struct man data;
  struct Man * next;
}book, * bookLink;


void menu()
{
  puts("\n\n");
  puts("\t\t|------------------------------------------------------|");
  puts("\t\t|                   Booking Tickets                    |");
  puts("\t\t|------------------------------------------------------|");
  puts("\t\t|       0:quit the system                              |");
  puts("\t\t|       1:Insert a train information                   |");
  puts("\t\t|       2:Search a train information                   |");
  puts("\t\t|       3:Book a train ticket                          |");
  puts("\t\t|       4:Modify the train information                 |");
  puts("\t\t|       5:Show the train information                   |");
  puts("\t\t|       6:save information to file                     |");
  puts("\t\t|------------------------------------------------------|");
}

/*遍历内存中的火车信息，保存火车信息到文件中*/
void SaveTrainInfo(Link l)
{
  FILE * fp;
  Node * p;
  int count = 0; 
  int flag = 1;

  fp = fopen("D:\\GitHub\\C6\\ticketBookingSystem\\train.txt", "ab+");
  if(fp == NULL)
  {
    printf("the file can't be opened!");
    return ;
  }

  p = l->next;
  while (p)
  {
    if(fwrite(p, sizeof(Node), 1, fp) == 1)
    {
      p = p->next;      /*p指向的节点向后移一个，也就是p被重新赋值了，移情别恋了，p不再指向原节点，指向下一个节点了*/
      count++;
    }
    else{
      flag = 0;
      printf("保存火车信息到文件中发生错误\n");
      break;
    }
  }

  if(flag)
  {
    printf(" saved %d train records\n",count);
    saveflag = 0;
  }

  fclose(fp);
}

/*遍历内存中的订票人信息，保存订票人信息到文件中*/
void SaveBookInfo(bookLink k)
{
  FILE * fp;
  book * p;
  int count = 0; 
  int flag = 1;

  fp = fopen("D:\\GitHub\\C6\\ticketBookingSystem\\man.txt", "ab+");
  if(fp == NULL)
  {
    printf("the file can't be opened!");
    return ;
  }

  p = k->next;
  while (p)
  {
    if (fwrite(p, sizeof(book), 1, fp) == 1)
    {
      p = p->next;
      count++;
    }else{
      flag = 0;
      printf("保存订票人信息到文件中发生错误\n");
      break;
    }
  }

  if (flag)
  {
    printf(" saved %d man records\n",count);
    saveflag = 0;
  }

  fclose(fp);
}

/*插入一个火车票信息*/
void InsertTrainInfo(Link linkhead)         /*链表名是头指针名，头指针指向头结点*/
{
  Node * p, * r, *s;
  char num[10];                       /*列车名*/
  r = linkhead;                       /*r指向头结点*/
  s = linkhead->next;
  while (r->next != NULL)             /*尾插法，让r指向最后一个节点，即r->next == NULL*/
    r = r->next;                
  while (1)
  {
    printf("please input the number of the train(0-return)");
    scanf("%s",num);
    if (strcmp(num, "0") == 0)
      break;
    /*判断是否已经存在*/
    while (s)                         /*遍历链表*/
    {
      if (strcmp(s->data.num, num) == 0)
      {
        printf("the train '%s'is existing!\n",num);
        return;                                           /*直接return，从被调函数返回主调函数继续执行*/
      }
      s = s->next;
    }
    
    /*不存在，执行添加火车信息操作*/
    p = (Node *)malloc(sizeof(Node));
    strcpy(p->data.num, num);                                    /*输入车号*/
    printf("Input the city where the train will start:");
    scanf("%s", p->data.startcity);
    printf("Input the city where the train will reach:");
    scanf("%s", p->data.reachcity);
    printf("Input the time which the train take off:");
    scanf("%s", p->data.takeofftime);
    printf("Input the time which the train receive:");
    scanf("%s", p->data.receivetime);
    printf("Input the price of ticket:");
    scanf("%d",&p->data.price);
    printf("Input the number of booked tickets:");
	  scanf("%d",&p->data.ticketNum);                               /*输入票数*/
    p->next = NULL;
    r->next = p;                  /*p是尾结点*/
    r = p;                        /*r重新被赋为尾结点*/
    saveflag = 1;
    return;
  }
}

/*打印火车票信息*/
void printHeader()                /*格式化输出表头*/
{
  printf(HEADER1);
  printf(HEADER2);
  printf(HEADER3);
}
void printdata(Node *q)
{
  Node * p;
  p = q;
  printf(FORMAT, DATA);           /*格式化输出表中数据*/
}

/*打印所有火车信息*/
void showtrain(Link linkhead)
{
  Node *p;
  p = linkhead->next;
  printHeader();
  if(p == NULL)
    printf("no records!");
  else
    while(p!=NULL)
    {       
      printdata(p);
	    p=p->next;
    }
}

/*查询某一列火车信息*/
void searthtrain(Link linkhead)
{
  Node *s[10], * p;
  char num[10];
  char reachcity[10];
  int sel;
  int k;
  int i = 0;
  p = linkhead->next;

  if(!p)
  {
    printf("\nThere is not any record !\n");
    return;
  }

  printf("Choose the way:\n1:according to the number of train;\n2:according to the city:\n");
  scanf("%d", &sel);
  if (sel == 1)
  {
    printf("Input the number of the train:");
    scanf("%s", num);                                 /*按列车号查找，唯一对应*/
    while (p)
    {
      if (strcmp(p->data.num, num) == 0)
      {
        s[i] = p;
        i++;
        break;
      }
      p = p->next;
    }
  }
  if (sel == 2)
  {
    printf("Input the city you want to go:");
    scanf("%s", reachcity);                           /*按到达城市查找*/
    while (p)
    {
      if (strcmp(p->data.reachcity, reachcity) == 0)
      {
        s[i] = p;
        i++;
        p = p->next;
      }
      p = p->next;
    }
  }

  if (i == 0)
    printf("\ncan't find!\n");
  else{
    printHeader();
    for (k = 0; k < i; k++)
    {
      printdata(s[k]);
    }
  }
}

/*修改火车票信息*/
void Modifytrain(Link linkhead)
{
  Node * p;
  char ch;
  char num[10];
  int sel, i;

  p = linkhead->next;

  if(!p)
  {
    printf("\nthere isn't record for you to modify!\n");
    return;
  }

  printf("\nDo you want to modify it?(y/n)\n");
  getchar();
  scanf("%c", &ch);
  if (ch == 'y' || ch == 'Y')
  {
    printf("Input the number of the train:");
    scanf("%s", num);                                 /*按列车号查找并修改*/
    while (p)
    {
      if (strcmp(p->data.num, num) == 0)
      {
        printf("Input new number of train:");
        scanf("%s",&p->data.num);
		    printf("Input new city the train will start:");
        scanf("%s",&p->data.startcity);
        printf("Input new city the train will reach:");
        scanf("%s",&p->data.reachcity);
        printf("Input new time the train take off");
		    scanf("%s",&p->data.takeofftime);
        printf("Input new time the train reach:");
		    scanf("%s",&p->data.receivetime);
        printf("Input new price of the ticket::");
        scanf("%d",&p->data.price);
        printf("Input new number of people who have booked ticket:");
        scanf("%d",&p->data.ticketNum);
        printf("\nmodifying record is sucessful!\n");
        i++;
        saveflag = 1;
        break;
      }
      p = p->next;
    }
  }

  if (i == 0)
    printf("can't find!\n");
}


/*订票子模块*/
void Bookticket(Link linkhead, bookLink bookhead)
{
  Node * p;
  Node *s[10];
  book * q, * h;
  char reachcity[10], num[10];
  char ch;
  int k, flag;
  int i = 0;

  p = linkhead->next;
  q = bookhead;                                         /*q指向头结点*/
  while (q->next!=NULL)                                 /*循环，让q指向最后一个节点，即q->next == NULL*/
    q = q->next;

  printf("Input the city you want to go: ");
  scanf("%s", reachcity);                               
  while(p)                                              /*遍历链表，查找是否有要到达的城市火车票*/
  {
    if (strcmp(p->data.reachcity, reachcity) == 0)
    {
      s[i] = p;                                         /*所有到达城市的火车信息存储到结构体指针数组s中*/
      i++;
    }
    p = p->next;                                        /*遍历，当p是最后一个节点时，p->next == NULL，遍历循环停止*/
  }
  printf("\n\nthe number of record have %d\n",i);
  printHeader();
  for (k = 0; k < i; k++)
  printdata(s[k]);

  if (i == 0)                                           /*没有则提示无，有则显示列车号*/
    printf("\ncan't find the city you want to go.\n");
  else
  {
    printf("\ndo you want to book?<y/n>\n");            /*开始订票*/
    getchar();
    scanf("%c", &ch);
    if (ch == 'y' || ch == 'Y')
    {
      printf("please input the number of the train:");  
	    scanf("%s",num);                                  /*输入要定的列车号*/
      for (k = 0; k < i; k++)
      {
        if (strcmp(s[k]->data.num, num) == 0)
        {
          flag = 1;
          if(s[k]->data.ticketNum < 1)                  /*验证该列车号有没有票*/
          {
            printf("\nno ticket!\n");
            return;
          }  
          else{
            printf("remain %d tickets\n",s[k]->data.ticketNum);
            h = (book *)malloc(sizeof(book));
            if(h)
            {
              printf("input your id:\n");
              scanf("%s", h->data.num);
              printf("input your name:\n");
              scanf("%s", h->data.name);
              printf("input your bookNum:\n");
              scanf("%d", &h->data.bookNum);
              printf("\nLucky!you have booked a ticket!");
              h->next = NULL;
              printf("\nLucky!you have booked a ticket!");
              q->next = h;
              printf("\nLucky!you have booked a ticket!");
              q = h;
              printf("\nLucky!you have booked a ticket!");
              getch();
              saveflag=1;
            }
            
          }
        }
          
      }
      if(flag == 0)
        printf("\ninput error\n");
    }
  }
}









int main(void)
{
  FILE * fp1, * fp2;

  Node * p, *r;
  Link l;               /*链表名是头指针名，头指针指向头结点。l指向头结点，节点是结构体*/
  book * t, * h;
  bookLink k;

  int sel;
  char ch1;

  l = (Node *)malloc(sizeof(Node));       
  l->next = NULL;
  r = l;                                  /*尾结点*/
  k = (book *)malloc(sizeof(book));
  k->next = NULL;                     
  h = k;                                  /*尾结点*/

  fp1 = fopen("D:\\GitHub\\C6\\ticketBookingSystem\\train.txt", "ab+");   /*打开存储车票信息的文件*/
  if (fp1 == NULL)
  {
    printf("can't open the file: train.txt\n");
    return 0;
  }
  while(feof(fp1) == 0)   /*若文件中有数据，执行循环体中的语句，构造链表，读取该磁盘文件中的数据，储存在内存中*/
  {
    p = (Node *)malloc(sizeof(Node));       /*为链表节点分配内存，指针p指向该节点，p的值是该节点的内存地址*/    
    if(fread(p, sizeof(Node), 1, fp1) == 1) /*将fp1待读取文件数据拷贝进p指向的节点中*/
    {
      p->next = NULL;
      r->next = p;
      r = p;                                  /*尾结点*/
    }
  }
  fclose(fp1); 

  fp2=fopen("D:\\GitHub\\C6\\ticketBookingSystem\\man.txt","ab+");
  if((fp2==NULL))
  {
    printf("can't open the file!");
    return 0;
  } 
  while(!feof(fp2))   /*若文件中有数据，执行循环体中的语句，构造链表，读取该磁盘文件中的数据，储存在内存中*/
  {
    t=(book*)malloc(sizeof(book));
    if(fread(t,sizeof(book),1,fp2)==1)
    {
      t->next = NULL;
      h->next = t;
      h = t;
    }
  }
  fclose(fp2);

  while(1)
  {
    system("CLS");
    menu();
    printf("\tplease choose(0~6), 0 to save and quit: ");
    scanf("%d", &sel);
    switch (sel)                  /*根据输入的sel值不同选择相应操作*/
    {
      case 0:
        if (saveflag == 1)        /*当退出时判断信息是否保存*/
        {
          getchar();
          printf("\nthe file have been changed!do you want to save it(y/n)?\n");
          scanf("%c", &ch1);
          if (ch1 == 'y' || ch1 == 'Y')
          {
            SaveBookInfo(k);
            SaveTrainInfo(l);
          }
        }
        printf("\nThank you!!You are welcome too\n");
        break;

      case 1:
        InsertTrainInfo(l);
        break;
      
      case 2:
        searthtrain(l);
        break;

      case 3:
        Bookticket(l,k);
        break;

      case 4:
        Modifytrain(l);
        break;
      
      case 5:
        showtrain(l);
        break;
      
      case 6:
        SaveBookInfo(k);
        SaveTrainInfo(l);
        break;
      
      default:
        break;
    }

    printf("\nplease press any key to continue.......");
    getch();
  }

  return 0;
}