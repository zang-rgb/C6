#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i = 0;
    int j = 0;
    int *a=(int*)malloc(sizeof(int)*2);
    for( i=0;i<numsSize-1;i++)
    {
        for( j=i+1;j<numsSize;j++)
        {
            if(nums[i]+nums[j]==target)
            {
                a[0]=i;
                a[1]=j;
                * returnSize = 2;
                return a;
            }
        }
    }
    return NULL;
}

int main(void)
{
    //int nums[] = {-1, -2, -3, -4, -5};
    //int target = -8;
    //int nums[] = {0,4,3,0};
    //int target = 0;
    int nums[] = { 3, 2, 3 };
    int size = sizeof(nums) / sizeof(*nums);
    int target = 5;
    int count = 0;
    int *indexes = twoSum(nums, size, target, &count);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }
    return 0;
}