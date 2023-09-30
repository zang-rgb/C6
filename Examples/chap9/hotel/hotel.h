/*hotel.h -- 符号常量和hotel.c中所有函数的函数原型*/
#define QUIT 5
#define HOTEL1  180.00
#define HOTEL2  225.00
#define HOTEL3  255.00
#define HOTEL4  355.00
#define DSICOUNT 0.95
#define STARS   "**************************"

int menu(void);
int getnights(void);
void showprice(int nights, double rate);