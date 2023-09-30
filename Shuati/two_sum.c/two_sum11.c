#include <stdio.h>
#include <stdlib.h>
/*
struct object
{
  int val;
  int index;
};
*/

int compare(const void * p1, const void * p2)
{
  const int * a1 = (const int *) p1; // 强制转换得到类型正确的指针。
  const int * a2 = (const int *) p2;
  return *a1 - *a2;  // 为了比较指针所指向的int值，必须解引用指针。
}
  

int * twosum(int * nums, int numsSize, int target, int * returnSize)  // 改变了原数组
{
  int * a = (int *)malloc(2 * sizeof(int));
  qsort(nums, numsSize, sizeof(int), compare);
  int i = 0;
  int j = numsSize - 1;
  for (i = 0; i < numsSize; i++)
    printf("%d", nums[i]);
  putchar('\n');
  i = 0;
  while (i < j)
  {
    if (nums[i] + nums[j] < target)
      i++;
    else if(nums[i] + nums[j] > target)
      j--;
    else
    {
      a[0] = i;
      a[1] = j;
      *returnSize = 2;
      return a;
    }
  }
  return NULL;
}


int main(void)
{
  int nums[] = {3, 2, 1};
  int numsSize = sizeof(nums) / sizeof(* nums); // 即sizeof(nums[0])
  int target = 5;
  int count = 0;
  int i;
  for (i = 0; i < numsSize; i++)
    printf("%d", nums[i]);
  putchar('\n');
  int * result = twosum(nums, numsSize, target, &count);
  
  if (result)
    printf("%d %d", result[0], result[1]);
  else
    printf("Not Found!\n");

  return 0;
}