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

    int nums[5] = {11, 12, 14, 15, 17};
    int target = 25;
    int returnSize = 0;

    int *resultidx = twoSum(nums, 5, target, &returnSize);

    printf("target:%3d == (%3d + %3d)", target , nums[resultidx[0]], nums[resultidx[1]]);

    free(resultidx);
   return 0;
}
