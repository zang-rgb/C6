/*
��Ŀ�����������ڼ��ĵ�һ����ĸ���ж�һ�������ڼ��������һ����ĸһ����������жϵڶ�����ĸ��

�����������������ȽϺã������һ����ĸһ�������ж����������if����жϵڶ�����ĸ��
*/

#include <stdio.h>

int main(void)
{
  printf("����һ���������ĸ");
  char i, j;
  scanf("%c", &i);
  getchar();
  switch (i)
  {
  case 'm':
    printf("monday\n");
    break;

  case 't':
    printf("����һ����ݵڶ�����ĸ");
    scanf("%c", &j);
    switch (j)
    {
    case 'u':
      printf("tuesday\n");
      break;
    case 'h':
      printf("thursday\n");
      break;
    default:
      break;
    }
    break;

  case 'w':
    printf("wednesday\n");
    break;

  case 'f':
    printf("friday\n");
    break;

  case 's':
    printf("����һ����ݵڶ�����ĸ");
    scanf("%c", &j);
    switch (j)
    {
    case 'a':
      printf("saturday\n");
      break;
    case 'u':
      printf("sunday\n");
      break;
      
    default:
      printf("error\n");
      break;
    }
    break;

  default:
    break;
  }
  return 0;
}