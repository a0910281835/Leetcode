#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/**
 Target :
 Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 * Note1: The returned array must be malloced, assume caller calls free().
 * Note2: retrunSize default is 0
 */
void swap(void *var1,void *var2, size_t size)
{
    void *temp = malloc(size);
    memcpy(temp, var1, size);
    memcpy(var1, var2, size);
    memcpy(var2, temp, size);
}


int compareInt(const void *var1, const void *var2)
{
    int ret = 0;
    int val1 = *((int *)var1);
    int val2 = *((int *)var2);

    if (val1 > val2) ret = 1;

    return ret;
}


void BubbleSort(void *base, size_t n, size_t size, int (*compare)(const void *, const void *))
{
    int idx1, idx2;

    for (idx1 = n - 1; idx1 >= 0 ; idx1--) // Do n times
    {
        for (idx2 = 0; idx2 < idx1; idx2++) // n-1
        {
            int swapFalg = compare((base + (idx2 * size)), (base + ((idx2 + 1) * size)));

            if (swapFalg)
            {
                swap((base + (idx2 * size)), (base + ((idx2 + 1) * size)), size);
            }
        }
    }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    unsigned int index1, index2;
    unsigned int sum;
    int *array = malloc(sizeof(int) * 2);

    for (index1 = 0; index1 < numsSize; index1++)
    {
        for (index2 = index1 + 1; index2 < numsSize; index2++)
        {
            sum =  nums[index1] + nums[index2];

           if (sum == target)
           {
               array[0] = index1;
               array[1] = index2;
               *returnSize  = 2;
               break;
           }


        }
    }

    return array;
}
int main(void)
{

    int numsSize = 9;
    int nums[] = {15, -2, 12, 3, -1, 10, -9, 14, 21};
    int target = 26;
    int returnSize = 0;

    int *resultidx = twoSum(nums, numsSize, target, &returnSize);

    printf("target:%3d == (%3d + %3d)\n", target , nums[resultidx[0]], nums[resultidx[1]]);

    free(resultidx);



    /* Test Sort */
    BubbleSort(nums, numsSize, sizeof(int), compareInt);

    int index = 0;
    for (index = 0; index < numsSize; index++)
    {
        printf("%2d\n", nums[index]);
    }
    /* Test Compare function

    int comVal1 = 12, comVal2 = 11;
    printf("%d\n", compareInt(&comVal1, &comVal2));

    */


    /* Test swap function
    int swap_var1 = 10, swap_var2 = 11;
    swap(&swap_var1, &swap_var2, sizeof(int));
    printf("%2d,%2d\n", swap_var1, swap_var2);
    */
   return 0;
}
