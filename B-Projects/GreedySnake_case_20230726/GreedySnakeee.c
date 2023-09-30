#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

               //windows DOS窗口中行列的原点为左上角，横纵坐标的原点也为左上角。行是纵坐标，列是横坐标。

#define ROW 22 //游戏区行数（指的是■的行数）
#define COL 42 //游戏区列数（指的是■的列数）
              
               //在本例中，对于一个■， 一行一列 占用 一个纵坐标两个横坐标。
               //以行列位置为基准 --> 求纵坐标横坐标的值。即行=纵坐标，列*2=横坐标。

               

#define KONG 0 //标记空（什么也没有）
#define WALL 1 //标记墙
#define FOOD 2 //标记食物
#define HEAD 3 //标记蛇头
#define BODY 4 //标记蛇身

#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
#define SPACE 32 //暂停
#define ESC 27 //退出

//蛇头
struct Snake{
  int len;    //记录蛇身长度
  int row;      //蛇头行（行 = 纵坐标）
  int col;      //蛇头列（列*2 = 横坐标）
}snake;

//蛇身
struct Body
{
  int row;      //蛇身行（行 = 纵坐标）
  int col;      //蛇身列（列*2 = 横坐标）
}body[ROW*COL];   //开辟足以存储蛇身的结构体数组

int face[ROW][COL];   //标记游戏区各个位置的状态，ROW是行，COL是列。

//隐藏光标
void HideCursor();
//光标跳转
void CursorJump(int x, int y);
//初始化界面
void InitInterface();
//颜色设置
void color(int c);
//从文件读取最高分
void ReadGrade();
//更新最高分到文件
void WriteGrade();
//初始化蛇位置（此函数中没有将蛇打印出来）
void InitSnake();
//随机生成食物
void RandFood();
//判断得分与结束
void JudgeFunc(int col, int row);
//打印蛇与覆盖蛇尾（这里所说的蛇尾指的就是最后一个格子）
void DrawSnake(int flag);
//移动蛇
void MoveSnake(int col, int row);
//根据按键值所代表的行列位置更新，贪吃蛇以此移动一格（方向可以变也可以不变）
void run(int col, int row);
//游戏主体逻辑函数
void Game();

int max, grade;     //全局变量

int main()
{
#pragma warning (disable:4996) //消除警告
	max = 0, grade = 0; //初始化变量
	system("title 贪吃蛇"); //设置cmd窗口的名字
	system("mode con cols=84 lines=23"); //设置cmd窗口的大小
	HideCursor(); //隐藏光标
	ReadGrade(); //从文件读取最高分到max变量
	InitInterface(); //初始化界面
	InitSnake(); //初始化蛇位置（此函数中没有将蛇打印出来）
	srand((unsigned int)time(NULL)); //设置随机数生成起点
	RandFood(); //随机生成食物
	DrawSnake(1); //打印初始化蛇
	Game(); //开始游戏
	return 0;
}

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量
	curInfo.dwSize = 1; //如果没赋值的话，光标隐藏无效
	curInfo.bVisible = FALSE; //将光标设置为不可见
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorInfo(handle, &curInfo); //设置光标信息
}

//光标跳转
void CursorJump(int x, int y)
{
	COORD pos; //定义光标位置的结构体变量
	pos.X = x; //横坐标
	pos.Y = y; //纵坐标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorPosition(handle, pos); //设置光标位置
}

//初始化界面
void InitInterface()
{
  color(6); //颜色设置为土黄色
  int row; //行
  int col; //列
  for (row = 0; row < ROW; row++)
  {
    for (col = 0; col < COL; col++)
    {
      if (col == 0 || col == COL-1)
      {
        face[row][col] = WALL; //标记该位置为墙
        CursorJump(2 * col, row);   
        printf("■");
      }
      else if(row == 0 || row == ROW -1)
      {
        face[row][col] = WALL; //标记该位置为墙
        printf("■");
      }
      else{
        face[row][col] = KONG; //标记该位置为空
      }
    }
  }
}

//颜色设置
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
	//注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}

//从文件读取最高分
void ReadGrade()
{
  FILE* fp = fopen("贪吃蛇最高得分记录.txt", "r"); //以只读的方式打开文件
  if (fp == NULL) //打开文件失败
  {
    fp = fopen("贪吃蛇最高得分记录.txt", "r"); //以只写的方式打开文件
    fwrite(&max, sizeof(int), 1, fp); //将max写入文件（此时max为0），即将最高得分初始化为0
  }
  fseek(fp, 0, SEEK_SET); //使文件指针fp指向文件开头
  fread(&max, sizeof(int), 1, fp); //读取文件当中的最高得分到max当中
  fclose(fp); //关闭文件
  fp = NULL; //文件指针及时置空
}

//更新最高分到文件
void WriteGrade()
{
  FILE * fp = fopen("贪吃蛇最高得分记录.txt", "w");
  if (fp == NULL)
  {
    printf("保存最高分失败！");
    exit(0);
  }
  fwrite(&grade, sizeof(int), 1, fp);
  fclose(fp);
  fp = NULL;
}

//初始化蛇位置（此函数中没有将蛇打印出来）
void InitSnake()
{
  snake.len = 2;      //蛇的身体长度初始化为2
  snake.row = ROW / 2;  //蛇头位置的行
  snake.col = COL / 2;  //蛇头位置的列
  //蛇身坐标的行和列
  body[0].row = ROW / 2;
  body[0].col = COL / 2 - 1;
  body[1].row = ROW / 2;
  body[1].col = COL / 2 - 2;
  //将蛇头和蛇身位置进行标记
  face[snake.row][snake.col] = HEAD;
  face[body[0].row][body[0].col] = BODY;
  face[body[1].row][body[1].col] = BODY;
}

//随机生成食物
void RandFood()
{
  int row;
  int col;

  do
  {
    //随机生成食物的行列位置
    row = rand() % ROW; //行
    col = rand() % COL; //列
  } while (face[row][col] != KONG); //确保生成食物的位置为空，若不为空则重新生成
  face[row][col] = FOOD;
  color(12);
  CursorJump(2*col, row); //行=纵坐标，列*2=横坐标
  printf("●");  
}

//判断得分与结束---void RandFood()
void JudgeFunc(int row, int col)
{
  //若蛇头即将到达的位置是食物，则得分
  if (face[snake.row + row][snake.col + col] == FOOD)
  {
    snake.len++;
    grade += 10;
    color(7);
    CursorJump(0, ROW);
    printf("当前得分：%d", grade);
    RandFood();
  }
  //若蛇头即将到达的位置是墙或者蛇身，则游戏结束
  else if (face[snake.row + row][snake.col + col] == WALL || face[snake.row + row][snake.col + col] == BODY)
  {
    Sleep(1000);
    system("cls");
    color(7);
    CursorJump(2 * (COL / 3), ROW / 2 - 3);
    if(grade > max)
    {
      printf("恭喜你打破最高记录，最高记录更新为%d", grade);
			WriteGrade();
    }
    else if (grade == max)
		{
			printf("与最高记录持平，加油再创佳绩", grade);
		}
		else
		{
			printf("请继续加油，当前与最高记录相差%d", max - grade);
		}
    CursorJump(2 * (COL / 3), ROW / 2);
		printf("GAME OVER");
    while (1)
    {
      char ch;
      CursorJump(2 * (COL / 3), ROW / 2 + 3);
			printf("再来一局?(y/n):");
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
				printf("选择错误，请再次选择");
			}
    }
  }
}

//打印蛇与覆盖蛇尾
void DrawSnake(int flag)
{
  if (flag == 1)
  {
    color(10);
    CursorJump(2*snake.col, snake.row);
    printf("■"); //打印蛇头
    for (int i = 0; i < snake.len; i++)
    {
      CursorJump(2*body[i].col, body[i].row);
      printf("□"); //打印蛇身
    }
  }
  else //覆盖蛇尾
  {
    if (body[snake.len - 1].col != 0) //防止len++后将(0, 0)位置的墙覆盖
    {
      //将蛇尾覆盖为空格即可
      CursorJump(2*body[snake.len - 1].col, body[snake.len - 1].row);
      printf("  ");
    }
  }
}

//蛇移动（方向可以变也可以不变，蛇身可以有曲折，蛇移动的本质就是包括蛇头蛇身的所有格子更新，以行列为基准）---void DrawSnake(int flag)
//包括标记更新和位置更新
void MoveSnake(int row, int col)
{
  //***标记更新
	DrawSnake(0); //将蛇尾的最后一个格子更新为空格
	face[body[snake.len - 1].row][body[snake.len - 1].col] = KONG; //蛇移动后原来的蛇尾标记为空
	face[snake.row][snake.col] = BODY; //蛇移动后蛇头的位置变为蛇身

  //***位置更新：逻辑从蛇尾到蛇头，原来第i-1个蛇身的格子变为移动后第i个蛇身的格子
  //蛇移动后各个蛇身位置坐标需要更新
	for (int i = snake.len; i > 0; i--)
  {
    //以行列位置基准，原来第i-1个蛇身的格子变为移动后第i个蛇身的格子；i-1赋值给i
    body[i].row = body[i-1].row; 
    body[i].col = body[i-1].col;
  }
  //原来蛇头位置信息变为移动后第0个蛇身的位置信息
  body[0].row = snake.row;
  body[0].col = snake.col;
  //移动后蛇头的位置更改
  snake.row = snake.row + row;
  snake.col = snake.col + col;
  //打印移动后的蛇
	DrawSnake(1); 
}

//根据按键值所代表的行列位置更新，贪吃蛇以此移动一格（方向可以变也可以不变）---void JudgeFunc(int row, int col),void MoveSnake(int row, int col)
void run(int row, int col)
{
  int t = 0;
  while (1)
  {
    if (t == 0)
      t = 5000; //这里t越小，蛇移动速度越快（可以设置游戏难度）
    while (--t)
    {
      if (kbhit() != 0) //若键盘被敲击，则退出循环
        break;
    }
    if (t == 0) //键盘未被敲击（上面的while(--t)循环会将t一直减为0）
    {
      JudgeFunc(row, col);
      MoveSnake(row, col);
    }
    else  //键盘被敲击(t不为0)
    {
      break;
    }
  } 
}

//游戏主体逻辑函数---void run(int row, int col)
void Game()
{
	int n = RIGHT; //开始游戏时，默认向右移动
  run(0, 1); //向右移动（行数不变，列数+1）
	int now = RIGHT; //记录当前蛇的移动方向，当前开始游戏时，默认向右移动
	while (1)
	{
		n = getch(); //读取键值

		//***第一个switch：在执行移动前，需要对所读取的按键根据当前蛇的移动方向进行调整
		switch (n)
		{
		case UP:
		case DOWN: //如果敲击的是“上”或“下”
			if (now != LEFT&&now != RIGHT) //并且当前蛇的移动方向不是“左”或“右”
			{
				n = now; //那么下一次蛇的移动方向设置为当前蛇的移动方向
			}
			break;
		case LEFT:
		case RIGHT: //如果敲击的是“左”或“右”
			if (now != UP&&now != DOWN) //并且当前蛇的移动方向不是“上”或“下”
			{
				n = now; //那么下一次蛇的移动方向设置为当前蛇的移动方向
			}
		case SPACE:
		case ESC:
		case 'r':
		case 'R':
			break; //这四个无需调整
		default:
			n = now; //其他键无效，默认为当前蛇移动的方向
			break;
		}

    //***第二个switch：根据调整后的键值执行一次变向/不变向移动
		switch (n)  
		{
		case UP: //方向键：上
			run(-1, 0); //向上移动（行数-1，列数不变）
			now = UP; //并记录当前蛇的移动方向
			break;
		case DOWN: //方向键：下
			run(1, 0); //向下移动（行数+1，列数不变）
			now = DOWN; //并记录当前蛇的移动方向
			break;
		case LEFT: //方向键：左
			run(0, -1); //向左移动（行数不变，列数-1）
			now = LEFT; //并记录当前蛇的移动方向
			break;
		case RIGHT: //方向键：右
			run(0, 1); //向右移动（行数不变，列数+1）
			now = RIGHT; //并记录当前蛇的移动方向
			break;
		case SPACE: //暂停
			system("pause>nul"); //暂停后按任意键继续
			break;
		case ESC: //退出
			system("cls"); //清空屏幕
			color(7); //颜色设置为白色
			CursorJump(COL - 8, ROW / 2);
			printf("  游戏结束  ");
			CursorJump(COL - 8, ROW / 2 + 2);
			exit(0);
		case 'r':
		case 'R': //重新开始
			system("cls"); //清空屏幕
			main(); //重新执行主函数
		}
	}
}
