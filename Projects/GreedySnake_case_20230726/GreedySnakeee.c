#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

               //windows DOS���������е�ԭ��Ϊ���Ͻǣ����������ԭ��ҲΪ���Ͻǡ����������꣬���Ǻ����ꡣ

#define ROW 22 //��Ϸ��������ָ���ǡ���������
#define COL 42 //��Ϸ��������ָ���ǡ���������
              
               //�ڱ����У�����һ������ һ��һ�� ռ�� һ�����������������ꡣ
               //������λ��Ϊ��׼ --> ��������������ֵ������=�����꣬��*2=�����ꡣ

               

#define KONG 0 //��ǿգ�ʲôҲû�У�
#define WALL 1 //���ǽ
#define FOOD 2 //���ʳ��
#define HEAD 3 //�����ͷ
#define BODY 4 //�������

#define UP 72 //���������
#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������
#define SPACE 32 //��ͣ
#define ESC 27 //�˳�

//��ͷ
struct Snake{
  int len;    //��¼������
  int row;      //��ͷ�У��� = �����꣩
  int col;      //��ͷ�У���*2 = �����꣩
}snake;

//����
struct Body
{
  int row;      //�����У��� = �����꣩
  int col;      //�����У���*2 = �����꣩
}body[ROW*COL];   //�������Դ洢����Ľṹ������

int face[ROW][COL];   //�����Ϸ������λ�õ�״̬��ROW���У�COL���С�

//���ع��
void HideCursor();
//�����ת
void CursorJump(int x, int y);
//��ʼ������
void InitInterface();
//��ɫ����
void color(int c);
//���ļ���ȡ��߷�
void ReadGrade();
//������߷ֵ��ļ�
void WriteGrade();
//��ʼ����λ�ã��˺�����û�н��ߴ�ӡ������
void InitSnake();
//�������ʳ��
void RandFood();
//�жϵ÷������
void JudgeFunc(int col, int row);
//��ӡ���븲����β��������˵����βָ�ľ������һ�����ӣ�
void DrawSnake(int flag);
//�ƶ���
void MoveSnake(int col, int row);
//���ݰ���ֵ�����������λ�ø��£�̰�����Դ��ƶ�һ�񣨷�����Ա�Ҳ���Բ��䣩
void run(int col, int row);
//��Ϸ�����߼�����
void Game();

int max, grade;     //ȫ�ֱ���

int main()
{
#pragma warning (disable:4996) //��������
	max = 0, grade = 0; //��ʼ������
	system("title ̰����"); //����cmd���ڵ�����
	system("mode con cols=84 lines=23"); //����cmd���ڵĴ�С
	HideCursor(); //���ع��
	ReadGrade(); //���ļ���ȡ��߷ֵ�max����
	InitInterface(); //��ʼ������
	InitSnake(); //��ʼ����λ�ã��˺�����û�н��ߴ�ӡ������
	srand((unsigned int)time(NULL)); //����������������
	RandFood(); //�������ʳ��
	DrawSnake(1); //��ӡ��ʼ����
	Game(); //��ʼ��Ϸ
	return 0;
}

//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //��������Ϣ�Ľṹ�����
	curInfo.dwSize = 1; //���û��ֵ�Ļ������������Ч
	curInfo.bVisible = FALSE; //���������Ϊ���ɼ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorInfo(handle, &curInfo); //���ù����Ϣ
}

//�����ת
void CursorJump(int x, int y)
{
	COORD pos; //������λ�õĽṹ�����
	pos.X = x; //������
	pos.Y = y; //������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorPosition(handle, pos); //���ù��λ��
}

//��ʼ������
void InitInterface()
{
  color(6); //��ɫ����Ϊ����ɫ
  int row; //��
  int col; //��
  for (row = 0; row < ROW; row++)
  {
    for (col = 0; col < COL; col++)
    {
      if (col == 0 || col == COL-1)
      {
        face[row][col] = WALL; //��Ǹ�λ��Ϊǽ
        CursorJump(2 * col, row);   
        printf("��");
      }
      else if(row == 0 || row == ROW -1)
      {
        face[row][col] = WALL; //��Ǹ�λ��Ϊǽ
        printf("��");
      }
      else{
        face[row][col] = KONG; //��Ǹ�λ��Ϊ��
      }
    }
  }
}

//��ɫ����
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //��ɫ����
	//ע��SetConsoleTextAttribute��һ��API��Ӧ�ó����̽ӿڣ�
}

//���ļ���ȡ��߷�
void ReadGrade()
{
  FILE* fp = fopen("̰������ߵ÷ּ�¼.txt", "r"); //��ֻ���ķ�ʽ���ļ�
  if (fp == NULL) //���ļ�ʧ��
  {
    fp = fopen("̰������ߵ÷ּ�¼.txt", "r"); //��ֻд�ķ�ʽ���ļ�
    fwrite(&max, sizeof(int), 1, fp); //��maxд���ļ�����ʱmaxΪ0����������ߵ÷ֳ�ʼ��Ϊ0
  }
  fseek(fp, 0, SEEK_SET); //ʹ�ļ�ָ��fpָ���ļ���ͷ
  fread(&max, sizeof(int), 1, fp); //��ȡ�ļ����е���ߵ÷ֵ�max����
  fclose(fp); //�ر��ļ�
  fp = NULL; //�ļ�ָ�뼰ʱ�ÿ�
}

//������߷ֵ��ļ�
void WriteGrade()
{
  FILE * fp = fopen("̰������ߵ÷ּ�¼.txt", "w");
  if (fp == NULL)
  {
    printf("������߷�ʧ�ܣ�");
    exit(0);
  }
  fwrite(&grade, sizeof(int), 1, fp);
  fclose(fp);
  fp = NULL;
}

//��ʼ����λ�ã��˺�����û�н��ߴ�ӡ������
void InitSnake()
{
  snake.len = 2;      //�ߵ����峤�ȳ�ʼ��Ϊ2
  snake.row = ROW / 2;  //��ͷλ�õ���
  snake.col = COL / 2;  //��ͷλ�õ���
  //����������к���
  body[0].row = ROW / 2;
  body[0].col = COL / 2 - 1;
  body[1].row = ROW / 2;
  body[1].col = COL / 2 - 2;
  //����ͷ������λ�ý��б��
  face[snake.row][snake.col] = HEAD;
  face[body[0].row][body[0].col] = BODY;
  face[body[1].row][body[1].col] = BODY;
}

//�������ʳ��
void RandFood()
{
  int row;
  int col;

  do
  {
    //�������ʳ�������λ��
    row = rand() % ROW; //��
    col = rand() % COL; //��
  } while (face[row][col] != KONG); //ȷ������ʳ���λ��Ϊ�գ�����Ϊ������������
  face[row][col] = FOOD;
  color(12);
  CursorJump(2*col, row); //��=�����꣬��*2=������
  printf("��");  
}

//�жϵ÷������---void RandFood()
void JudgeFunc(int row, int col)
{
  //����ͷ���������λ����ʳ���÷�
  if (face[snake.row + row][snake.col + col] == FOOD)
  {
    snake.len++;
    grade += 10;
    color(7);
    CursorJump(0, ROW);
    printf("��ǰ�÷֣�%d", grade);
    RandFood();
  }
  //����ͷ���������λ����ǽ������������Ϸ����
  else if (face[snake.row + row][snake.col + col] == WALL || face[snake.row + row][snake.col + col] == BODY)
  {
    Sleep(1000);
    system("cls");
    color(7);
    CursorJump(2 * (COL / 3), ROW / 2 - 3);
    if(grade > max)
    {
      printf("��ϲ�������߼�¼����߼�¼����Ϊ%d", grade);
			WriteGrade();
    }
    else if (grade == max)
		{
			printf("����߼�¼��ƽ�������ٴ��Ѽ�", grade);
		}
		else
		{
			printf("��������ͣ���ǰ����߼�¼���%d", max - grade);
		}
    CursorJump(2 * (COL / 3), ROW / 2);
		printf("GAME OVER");
    while (1)
    {
      char ch;
      CursorJump(2 * (COL / 3), ROW / 2 + 3);
			printf("����һ��?(y/n):");
      scanf("%c", &ch);
      if (ch == 'y' || ch == 'Y')
			{
				system("cls");
				main();
			}
			else if (ch == 'n' || ch == 'N')
			{
				CursorJump(2 * (COL / 3), ROW / 2 + 5);
				exit(0);
			}
			else
			{
				CursorJump(2 * (COL / 3), ROW / 2 + 5);
				printf("ѡ��������ٴ�ѡ��");
			}
    }
  }
}

//��ӡ���븲����β
void DrawSnake(int flag)
{
  if (flag == 1)
  {
    color(10);
    CursorJump(2*snake.col, snake.row);
    printf("��"); //��ӡ��ͷ
    for (int i = 0; i < snake.len; i++)
    {
      CursorJump(2*body[i].col, body[i].row);
      printf("��"); //��ӡ����
    }
  }
  else //������β
  {
    if (body[snake.len - 1].col != 0) //��ֹlen++��(0, 0)λ�õ�ǽ����
    {
      //����β����Ϊ�ո񼴿�
      CursorJump(2*body[snake.len - 1].col, body[snake.len - 1].row);
      printf("  ");
    }
  }
}

//���ƶ���������Ա�Ҳ���Բ��䣬������������ۣ����ƶ��ı��ʾ��ǰ�����ͷ��������и��Ӹ��£�������Ϊ��׼��---void DrawSnake(int flag)
//������Ǹ��º�λ�ø���
void MoveSnake(int row, int col)
{
  //***��Ǹ���
	DrawSnake(0); //����β�����һ�����Ӹ���Ϊ�ո�
	face[body[snake.len - 1].row][body[snake.len - 1].col] = KONG; //���ƶ���ԭ������β���Ϊ��
	face[snake.row][snake.col] = BODY; //���ƶ�����ͷ��λ�ñ�Ϊ����

  //***λ�ø��£��߼�����β����ͷ��ԭ����i-1������ĸ��ӱ�Ϊ�ƶ����i������ĸ���
  //���ƶ����������λ��������Ҫ����
	for (int i = snake.len; i > 0; i--)
  {
    //������λ�û�׼��ԭ����i-1������ĸ��ӱ�Ϊ�ƶ����i������ĸ��ӣ�i-1��ֵ��i
    body[i].row = body[i-1].row; 
    body[i].col = body[i-1].col;
  }
  //ԭ����ͷλ����Ϣ��Ϊ�ƶ����0�������λ����Ϣ
  body[0].row = snake.row;
  body[0].col = snake.col;
  //�ƶ�����ͷ��λ�ø���
  snake.row = snake.row + row;
  snake.col = snake.col + col;
  //��ӡ�ƶ������
	DrawSnake(1); 
}

//���ݰ���ֵ�����������λ�ø��£�̰�����Դ��ƶ�һ�񣨷�����Ա�Ҳ���Բ��䣩---void JudgeFunc(int row, int col),void MoveSnake(int row, int col)
void run(int row, int col)
{
  int t = 0;
  while (1)
  {
    if (t == 0)
      t = 5000; //����tԽС�����ƶ��ٶ�Խ�죨����������Ϸ�Ѷȣ�
    while (--t)
    {
      if (kbhit() != 0) //�����̱��û������˳�ѭ��
        break;
    }
    if (t == 0) //����δ���û��������while(--t)ѭ���Ὣtһֱ��Ϊ0��
    {
      JudgeFunc(row, col);
      MoveSnake(row, col);
    }
    else  //���̱��û�(t��Ϊ0)
    {
      break;
    }
  } 
}

//��Ϸ�����߼�����---void run(int row, int col)
void Game()
{
	int n = RIGHT; //��ʼ��Ϸʱ��Ĭ�������ƶ�
  run(0, 1); //�����ƶ����������䣬����+1��
	int now = RIGHT; //��¼��ǰ�ߵ��ƶ����򣬵�ǰ��ʼ��Ϸʱ��Ĭ�������ƶ�
	while (1)
	{
		n = getch(); //��ȡ��ֵ

		//***��һ��switch����ִ���ƶ�ǰ����Ҫ������ȡ�İ������ݵ�ǰ�ߵ��ƶ�������е���
		switch (n)
		{
		case UP:
		case DOWN: //����û����ǡ��ϡ����¡�
			if (now != LEFT&&now != RIGHT) //���ҵ�ǰ�ߵ��ƶ������ǡ��󡱻��ҡ�
			{
				n = now; //��ô��һ���ߵ��ƶ���������Ϊ��ǰ�ߵ��ƶ�����
			}
			break;
		case LEFT:
		case RIGHT: //����û����ǡ��󡱻��ҡ�
			if (now != UP&&now != DOWN) //���ҵ�ǰ�ߵ��ƶ������ǡ��ϡ����¡�
			{
				n = now; //��ô��һ���ߵ��ƶ���������Ϊ��ǰ�ߵ��ƶ�����
			}
		case SPACE:
		case ESC:
		case 'r':
		case 'R':
			break; //���ĸ��������
		default:
			n = now; //��������Ч��Ĭ��Ϊ��ǰ���ƶ��ķ���
			break;
		}

    //***�ڶ���switch�����ݵ�����ļ�ִֵ��һ�α���/�������ƶ�
		switch (n)  
		{
		case UP: //���������
			run(-1, 0); //�����ƶ�������-1���������䣩
			now = UP; //����¼��ǰ�ߵ��ƶ�����
			break;
		case DOWN: //���������
			run(1, 0); //�����ƶ�������+1���������䣩
			now = DOWN; //����¼��ǰ�ߵ��ƶ�����
			break;
		case LEFT: //���������
			run(0, -1); //�����ƶ����������䣬����-1��
			now = LEFT; //����¼��ǰ�ߵ��ƶ�����
			break;
		case RIGHT: //���������
			run(0, 1); //�����ƶ����������䣬����+1��
			now = RIGHT; //����¼��ǰ�ߵ��ƶ�����
			break;
		case SPACE: //��ͣ
			system("pause>nul"); //��ͣ�����������
			break;
		case ESC: //�˳�
			system("cls"); //�����Ļ
			color(7); //��ɫ����Ϊ��ɫ
			CursorJump(COL - 8, ROW / 2);
			printf("  ��Ϸ����  ");
			CursorJump(COL - 8, ROW / 2 + 2);
			exit(0);
		case 'r':
		case 'R': //���¿�ʼ
			system("cls"); //�����Ļ
			main(); //����ִ��������
		}
	}
}
