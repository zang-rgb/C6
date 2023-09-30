/*r_drive0.c 测试rand0.c函数*/
/*与rand0.c一起编译*/
#include <stdio.h>
extern unsigned int rand0(void);

int main(void)
{
  int count = 0;

  for (count = 0; count < 5; count++)
    printf("%d\n", rand0());
  getchar();
  return 0;
}