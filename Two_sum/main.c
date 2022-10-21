#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef enum
{
    false,
    true
}BOOL_T;

typedef struct
{
    int val;
    int idx;
} NUMIDX_T;



NUMIDX_T numidx[2] =
{
    {.val = 10, .idx = 1},
    {.val = 7 , .idx = 2},
};
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

int compareStruct(const void *var1, const void *var2)
{
    int comResult = 0;
    int val1 = ((NUMIDX_T *)var1)->val;
    int val2 = ((NUMIDX_T *)var2)->val;

    if (val1 > val2) comResult = 1;

    return comResult;
}

/*
// This Algorithm has 2 action 1. compare 2. swap
// The Best result (Order Seqecnce) still have (n+1)*(n-1)/2 compare
void BubbleSort(void *base, size_t n, size_t size, int (*compare)(const void *, const void *))
{
    int idx1, idx2;

    for (idx1 = n - 1; idx1 > 0 ; idx1--) // Do n-1 times
    {
        for (idx2 = 0; idx2 < idx1; idx2++) // divid inorder and order term
        {
            int swapFalg = compare((base + (idx2 * size)), (base + ((idx2 + 1) * size)));

            if (swapFalg)
            {
                swap((base + (idx2 * size)), (base + ((idx2 + 1) * size)), size);
            }
        }
    }
}
*/

/*
// This Algorithm reduce compare time when seqence is order seqence
void BubbleSort(void *base, size_t n, size_t size, int (*compare)(const void*, const void *))
{
    BOOL_T inorderFlag = true;
    n--;

    while (inorderFlag)
    {
        inorderFlag = false;
        int idx = 0;
        for (idx = 0; idx < n; idx ++)
        {
            int swapFalg = compare((base + (idx * size)), (base + ((idx + 1) * size)));

            if (swapFalg)
            {
                swap((base + (idx * size)), (base + ((idx + 1) * size)), size);
                inorderFlag = true;
            }

        }

    }

}
*/

void BubbleSort(void *base, size_t n, size_t size, int (*compare)(const void *, const void *))
{
    int recordLastSwapIdx = n-1;
    BOOL_T inorderFlag = true;

    while (recordLastSwapIdx)
    {
        inorderFlag = false;
        int idx = 0;
        int everySwapIdx = 0;
        for (idx = 0; idx < recordLastSwapIdx; idx++)
        {
            int swapFalg = compare((base + (idx * size)), (base + ((idx + 1) * size)));

            if (swapFalg)
            {
                swap((base + (idx * size)), (base + ((idx + 1) * size)), size);
                everySwapIdx = idx;
                inorderFlag = true;
            }

        }
        recordLastSwapIdx = everySwapIdx;

    }
}


static int BinarySearch(const NUMIDX_T *ordernums, int leftidx, int rightidx, int target)
{
    int ret = -1;
    if ((ordernums[leftidx].val > target) || (ordernums[rightidx].val < target)) return -1;

    while(leftidx <= rightidx)
    {
        int mididx = (leftidx + rightidx) / 2;
        if ( target < ordernums[mididx].val)
        {
            rightidx = (mididx - 1);
        }
        else if (ordernums[mididx].val < target)
        {
            leftidx = (mididx + 1);
        }
        else
        {
            ret = mididx;
            return ret;
        }

    }

    return ret;
}

// Common Force Search method
/*
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
*/

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    NUMIDX_T numswithIdx[numsSize];
    int nowIdx = 0;
    int sum;
    int *array = malloc(sizeof(int) * 2);
    array[0] = -1;
    array[1] = -1;

    for (nowIdx = 0; nowIdx < numsSize; nowIdx++)
    {
        numswithIdx[nowIdx].idx = nowIdx;
        numswithIdx[nowIdx].val = nums[nowIdx];
    }
    // Sorting
    BubbleSort(numswithIdx, numsSize, sizeof(NUMIDX_T), compareStruct);
    int index = 0;
    for (index = 0; index < numsSize; index++)
    {
        printf("val:%2d,idx:%2d\n", numswithIdx[index].val, numswithIdx[index].idx);
    }

    for (nowIdx = 0; nowIdx < numsSize-1; nowIdx++)
    {
        int searchVal = target - numswithIdx[nowIdx].val;
        int idx2 =  BinarySearch(numswithIdx, (nowIdx + 1), (numsSize - 1), searchVal);

        if (idx2 >= 1)
        {
            array[0] = numswithIdx[nowIdx].idx;
            array[1] = numswithIdx[idx2].idx;
            break;
        }
    }
    return array;



}
int main(void)
{

    int numsSize = 9;
    int nums[] = {15, -2, 12, 3, -1, 10, -9, 14, 21};
    int target = 9;
    int returnSize = 0;

    int *resultidx = twoSum(nums, numsSize, target, &returnSize);

    printf("target:%3d idx:(%2d  %2d)\n", target , resultidx[0], resultidx[1]);

    free(resultidx);



    /*
    // Test common bubble Sort
    BubbleSort(nums, numsSize, sizeof(int), compareInt);

    int index = 0;
    for (index = 0; index < numsSize; index++)
    {
        printf("%2d\n", nums[index]);
    }
    */

    /*
    // Test Special Struct Bubble Sort
    int index = 0;

    NUMIDX_T numsWithIdx[numsSize];

    for (index = 0; index < numsSize; index++)
    {
        numsWithIdx[index].val = nums[index];
        numsWithIdx[index].idx = index;
    }


    for (index = 0; index < numsSize; index++)
    {
        printf("val:%2d,idx:%2d\n", numsWithIdx[index].val, numsWithIdx[index].idx);
    }


    BubbleSort(numsWithIdx, numsSize, sizeof(NUMIDX_T), compareStruct);
    //printf("%2d", (int )sizeof(NUMIDX_T));
    printf("----------\n");
    for (index = 0; index < numsSize; index++)
    {
        printf("val:%2d,oldidx:%2d, newidx:%2d\n", numsWithIdx[index].val, numsWithIdx[index].idx, index);
    }


    // Test Binary Seach in specail struct
    int ack = BinarySearch(numsWithIdx, 0, 8, 21);
    printf("%2d\n", ack);
    */
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
