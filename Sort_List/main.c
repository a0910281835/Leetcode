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
