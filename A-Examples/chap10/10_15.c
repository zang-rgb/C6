#include <stdio.h>

int main(void)
{
  int zippo[4][2] = { { 2, 4 }, { 6, 8 }, { 1, 3 }, {5, 7} };
  printf("   zippo = %p,    zippo + 1 = %p\n", zippo, zippo + 1);
  printf("zippo[0] = %p, zippo[0] + 1 = %p\n", zippo[0], zippo[0] + 1);//zippo[0]代表{2, 4}这个元素（数组），看作是{2,, 4}这个数组的数组名，打印出来是它的首元素2的地址，所以zippo[0] + 1打印出来是2后面的元素4的地址
  printf("  *zippo = %p,   *zippo + 1 = %p\n", *zippo, *zippo + 1);
  printf("zippo[0][0] = %d\n", zippo[0][0]);
  printf("  *zippo[0] = %d\n", *zippo[0]);
  printf("    **zippo = %d\n", **zippo);
  printf("        zippo[2][1] = %d\n", zippo[2][1]);
  printf("*(*(zippo + 2) + 1) = %d\n", *(*(zippo + 2) + 1));
  return 0;
}