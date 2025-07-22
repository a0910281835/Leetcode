#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _SELCTION_SORT

typedef struct ListNode* P_LIST_NODE_T;
typedef struct ListNode LIST_NODE_T;
typedef struct ListNode
{
    int val;
    P_LIST_NODE_T next;
    //struct LIST_NODE_T *next;
}LIST_NODE_T;

void printList(P_LIST_NODE_T pHead)
{
    P_LIST_NODE_T pNext = pHead;
    while (NULL != pNext)
    {
        printf("%d->", pNext->val);
        pNext= pNext->next;
    }
    printf("\n");
}

#if defined(_SELCTION_SORT)
P_LIST_NODE_T findPointerSmallVal(P_LIST_NODE_T pHead)
{
    P_LIST_NODE_T pSmallHead = pHead;
    P_LIST_NODE_T pNext = pHead;
    while ((NULL != pSmallHead) && (pNext != NULL))
    {
        if ((pSmallHead->val) > (pNext->val))
        {
            pSmallHead = pNext;
        }
        pNext = pNext->next;
    }
    return pSmallHead;
}

P_LIST_NODE_T changeSmallInList(P_LIST_NODE_T pHead, P_LIST_NODE_T pSmall)
{
    if (((NULL != pSmall) && (pSmall != pHead)) && (NULL != pHead))
    {
        P_LIST_NODE_T pTemp = pSmall->next;
        P_LIST_NODE_T pFather = pHead;
        while (pFather->next != pSmall)
        {
            pFather = pFather->next;
        }

        pFather->next = pTemp;

        pSmall->next = pHead;
        pHead = pSmall;
    }
    return pHead;
}

int checkList(P_LIST_NODE_T pHead)
{
    int retOrder = 1;
    if (NULL == pHead) return retOrder;
    P_LIST_NODE_T pNext = pHead;
    while ((1 == retOrder) && (NULL != pNext->next))
    {
        if (((pNext->next)->val) < (pNext->val)) retOrder = 0;
        pNext= pNext->next;
    }
    return retOrder;
}


P_LIST_NODE_T sortListInline(P_LIST_NODE_T pHead)
{
    int ret = 0;
    P_LIST_NODE_T pSmall;
    P_LIST_NODE_T pFather = pHead;
    P_LIST_NODE_T pNextHead = pHead;
    int first = 1;
    do
    {
        ret = checkList(pNextHead);
        pSmall = findPointerSmallVal(pNextHead);
        pNextHead = changeSmallInList(pNextHead, pSmall);
        if (1 != first)
        {
            pFather->next = pNextHead;
        }
        else
        {
            pHead = pNextHead;
            first = 0;
        }
        if (pHead == NULL) break;

        pFather = pNextHead;
        pNextHead = pNextHead->next;
    } while(0 == ret);


    return pHead;
}
#elif _MERGE_SORT

#define Move2(p) (p = (NULL == p->next) ? (p->next) : ((p->next)->next));
P_LIST_NODE_T retMidPointerBySlowAndFast(P_LIST_NODE_T pHead)
{
    P_LIST_NODE_T pSlow = pHead;
    P_LIST_NODE_T pFast = pHead;

    if (NULL != pFast) pFast = Move2(pFast);

    while (NULL != pFast)
    {
        pFast = Move2(pFast);
        pSlow = pSlow->next;
    }

    return pSlow;

}

P_LIST_NODE_T mergeTwoList(P_LIST_NODE_T pFirst, P_LIST_NODE_T pSecond)
{
    P_LIST_NODE_T pHead = malloc(sizeof(LIST_NODE_T));
    P_LIST_NODE_T pCurrent = pHead;
    //Using dummy node is easy here. if you don't use it, you need to flag / proof to avoid
    while ((NULL != pFirst) && (NULL != pSecond))
    {
        if ((pFirst->val) < (pSecond->val))
        {
            pCurrent->next = pFirst;
            pFirst = pFirst->next;
            pCurrent = pCurrent->next;
            pCurrent->next = NULL;// intrupt origin list
        }
        else
        {
            pCurrent->next = pSecond;
            pSecond = pSecond->next;
            pCurrent = pCurrent->next;
            pCurrent->next = NULL;// intrupt origin list
        }
    }

    if (NULL != pFirst)
    {
        pCurrent->next = pFirst;
    }
    else
    {
        pCurrent->next = pSecond;
    }

    P_LIST_NODE_T pDelete = pHead;
    pHead = pHead->next;
    free(pDelete);
    return pHead;
}

//-----------Merge Sort in List---------------------------//
P_LIST_NODE_T mergeSorListtRecursiveInline(P_LIST_NODE_T pHead)
{

    if ((NULL != pHead) && (NULL != (pHead->next)))
    {
        // set up slow and fast pointer
        P_LIST_NODE_T pFirst, pSecond;
        pFirst = pHead;
        // find intermediate pointer
        P_LIST_NODE_T pMed = retMidPointerBySlowAndFast(pHead);
        //printf("the next :%d\n",
        pSecond = (NULL != pMed) ? (pMed->next) : NULL;
        // divid two list
        if (NULL != pMed)
        {
            pMed->next = NULL;
        }
        // Recursive 2 part
        //MergeLedt
        pFirst  = mergeSorListtRecursiveInline(pFirst);
        //MegerRight
        pSecond = mergeSorListtRecursiveInline(pSecond);
        // Merge then
        pHead = mergeTwoList(pFirst, pSecond);
    }

    return pHead;
}


#endif





struct ListNode* sortList(struct ListNode* head)
{
#if defined(_SELCTION_SORT)
    head = sortListInline(head);
#elif _MERGE_SORT
    head = mergeSorListtRecursiveInline(head);
#endif

    return head;
}

struct ListNode* reverseList(struct ListNode* head)
{
    P_LIST_NODE_T pNewList = NULL;
    P_LIST_NODE_T pTemp    = NULL;

    //head    :5->4->3 //sigle list is FILO, then using two list can change direct.
    //newhead : NULL
    //temp ->4->3
    //head->next = NewList 5->
    //NewList = head;
    //head = tmep;
    while (NULL != head)
    {
        pTemp       = head->next;
        head->next  = pNewList;
        pNewList    = head;
        head        = pTemp;
    }

    return pNewList;
}

struct ListNode* reverseBetween(struct ListNode* head, int left, int right)
{
    P_LIST_NODE_T pLeft  = NULL;
    P_LIST_NODE_T pRight = NULL;
    P_LIST_NODE_T pDummy = malloc(sizeof(LIST_NODE_T));


    pDummy->next = head;
    head   = pDummy;
    pLeft  = head;
    pRight = head;

    if (left != right)
    {
        // 1->2->3->4 //2,3
        // 0->1->2->3->4
        // 1 3->4
        int idx =0;
        for (idx = 1; idx <= right; idx++)
        {
            if (idx < left)  pLeft  = pLeft->next;

            pRight = pRight->next;
        }
        pDummy = pRight;
        pRight = pRight->next;
        pDummy->next = NULL;

        pDummy = pLeft->next;
        pDummy = reverseList(pDummy);
        pLeft->next = pDummy;
        while(NULL != pDummy->next)
        {
            pDummy = pDummy->next;
        }
        pDummy->next = pRight;
    }

    pDummy = head;
    head   = head->next;
    free(pDummy);
}
/**
 *  * Note: The returned array must be malloced, assume caller calls free().
 *   */
// 0 1 2 3 4
// 4 2 9 0 -1

int * mergeTwoArray(int *nums, int leftHeadPos, int leftArraySize, int rightHeadPos, int rightArraySize, int *recordNums)
{
    if (leftArraySize + rightArraySize > 1)
    {
        int leftIdx  = 0;
        int rightIdx = 0;
        int newIdx   = 0;

        while ((leftIdx < leftArraySize) && (rightIdx < rightArraySize))
        {
            if (nums[leftHeadPos+leftIdx] <= nums[rightHeadPos+rightIdx])
            {
                recordNums[leftHeadPos+newIdx++] = nums[leftHeadPos+leftIdx++];
            }
            else
            {
                recordNums[leftHeadPos+newIdx++] = nums[rightHeadPos+rightIdx++];
            }
        }

        while (leftIdx < leftArraySize)
        {
            recordNums[leftHeadPos+newIdx++] = nums[leftHeadPos+leftIdx++];
        }
        while (rightIdx < rightArraySize)
        {
            recordNums[leftHeadPos+newIdx++] = nums[rightHeadPos+rightIdx++];
        }


        newIdx = 0;
        while (newIdx < (leftArraySize+rightArraySize))
        {
            nums[leftHeadPos+newIdx] = recordNums[leftHeadPos+newIdx];
            newIdx++;
        }

    }

    return nums;
}

int * mergeSortArray(int *nums, int leftHeadPos, int rightTailPos, int *recordNums)
{
// 0 1 2 3 4
// 4 1 3 5 2
// The only you need to concern is the basic condition
// 0 1
// 4 1
// 0 | 1
// recursive the only 0 and the another is 1
    if ((rightTailPos-leftHeadPos+1) > 1)
    {
        int mid = ((rightTailPos-leftHeadPos + 1) >> 1);
        //printf("leftPos:%d, Mid:%d rightTaPos%d\n",leftHeadPos, mid, rightTailPos);
        //printf("nums:%d,%d,%d,%d,%d\n", nums[0], nums[1], nums[2], nums[3], nums[4]);
        mergeSortArray(nums, leftHeadPos, leftHeadPos+mid-1, recordNums);// <----------------------------------this is key point
        //printf("sortingLeft nums:%d,%d,%d,%d,%d\n", nums[0], nums[1], nums[2], nums[3], nums[4]);
        mergeSortArray(nums, leftHeadPos+mid, rightTailPos, recordNums);
        //printf("sortingRight nums:%d,%d,%d,%d,%d\n", nums[0], nums[1], nums[2], nums[3], nums[4]);
        int leftArraySize  = mid;
        int rightArraySize = rightTailPos-leftHeadPos+1-mid;
        mergeTwoArray(nums, leftHeadPos, leftArraySize, leftHeadPos+mid, rightArraySize, recordNums);
        printf("MergeTwoPath nums:%d,%d,%d,%d,%d\n", nums[0], nums[1], nums[2], nums[3], nums[4]);
    }
    //else if (1 == (rightTailPos-leftHeadPos))
    //{
    //    if (nums[leftHeadPos] > nums[rightTailPos])
    //    {
    //        int temp = nums[leftHeadPos];
    //        nums[leftHeadPos]  = nums[rightTailPos];
    //        nums[rightTailPos] = temp;
    //    }

    //}


    return nums;
}

void swapData(int *first, int *second)
{
    int temp = *first;
    *first   = *second;
    *second  = temp;
}

//int findPivotFrom3Pos(int *array, int leftHeadIdx, int rightTailIdx)
int findPivotFrom3Pos(int *array, int size)
{
    if (size >= 3)
    {
        int midIdx = size >> 1;
        if (array[0] > array[midIdx]) swapData(array, array+midIdx);
        if (array[0] > array[size-1]) swapData(array, array+(size-1));
        if (array[midIdx] > array[size-1]) swapData(array+midIdx, array+(size-1));
        return midIdx;
    }
    return size;
}

//void quickSortByRecursive(int *array, int leftHeadIdx, int rightTailIdx)
void quickSortByRecursive(int *array, int size)
{
    if (size >= 3)
    {
        // How to Sorting
        // Choose a pivot to decide this point the last position.
        int midIdx = findPivotFrom3Pos(array, size);
        // Divid Two Sequence
        //In order to control code effect we put the mid to right-1

        // Recursive left
        // Recursive right
    }
    else
    {
        // Basic Conditon

    }
}


void QuickSort(int *array, int size)
{
    // InterFace
    quickSortByRecursive(array, size);
}

#define _MERGE_SORT_ARRAY
int* sortArray(int* nums, int numsSize, int* returnSize)
{
#if defined(_MERGE_SORT_ARRAY)
    int *recordNums = malloc(sizeof(int) * numsSize);
    nums = mergeSortArray(nums, 0, numsSize-1, recordNums);
    free(recordNums);
#elif defined(_QUICK_SORT_ARRAY)
#endif

    return nums;
}


int main(void)
{
    const int num = 5;
    int array[] = {4, 1, 3, 5, 2};
    P_LIST_NODE_T pHead = malloc(sizeof(LIST_NODE_T));
    P_LIST_NODE_T pNext = pHead;
    int i = 0;
    for (i = 0; i < num; i++)
    {
        pNext->val = array[i];
        pNext->next = ((num-1) == i) ? NULL : malloc(sizeof(LIST_NODE_T));
        pNext = pNext->next;
    }


    pNext = pHead;
    printf("origin list : ");
    printList(pHead);
    pHead = reverseList(pHead);
    printf("reverse list : ");
    printList(pHead);


    printf("test----sorting Array\n");
    int *returnSize = malloc(sizeof(int));
    sortArray(array, num, returnSize);

#if defined _SORT
    pNext = pHead;
    printf("before sorting : ");
    printList(pHead);
    pHead = sortListInline(pHead);
    //pHead = mergeSorListtRecursiveInline(pNext);
    printf("after sorting : ");
    printList(pHead);
    //pNext = retMidPointerBySlowAndFast(pNext);
    //printf("val:%d\n", pNext->val);
    //-----Using Seleciton Sort do list---------------------
    //pHead = sortListInline(pHead);
    //pNext = pHead;
    //printList(pHead);
    //while (pNext != NULL)
    //{
    //    printf("%d->", pNext->val);
    //    pNext = pNext->next;
    //}
#endif
   return 0;
}
