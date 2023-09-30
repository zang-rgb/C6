#include <stdio.h>
#include <stdlib.h>

struct object {
    int val;
    int index;
};

static int compare(const void *a, const void *b)
{
    return ((struct object *) a)->val - ((struct object *) b)->val;  // 比较的是struct object结构体变量，但是比较的方法是结构体变量中的val成员，不需要解引用该结构体指针。只要强制转换得到正确类型的指针即可。
    //((struct object *) a) 外面要加小括号，->运算符优先级高
}

int * twosum(int *nums, int numsSize, int target, int *returnSize)
{
    int i, j;
    struct object *objs = malloc(numsSize * sizeof(*objs)); //或者是sizeof(struct object)
    for (i = 0; i < numsSize; i++) {
        objs[i].val = nums[i];
        objs[i].index = i;
    }
    qsort(objs, numsSize, sizeof(*objs), compare); //或者是sizeof(struct object)
    
    int *results = malloc(2 * sizeof(int));
    i = 0;  // i必须要重新赋值为0，因为i在前面递增了
    j = numsSize - 1;
    while (i < j) {
        int sum = objs[i].val + objs[j].val;
        if (sum < target) {
            i++;
        } else if (sum > target) {
            j--;
        } else {
            results[0] = objs[i].index;
            results[1] = objs[j].index;
            *returnSize = 2;
            return results;
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
    int *indexes = twosum(nums, size, target, &count);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }

    return 0;
}