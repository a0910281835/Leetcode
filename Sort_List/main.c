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

#define REG (*(volatile unsigned int *)0x40001000)

void set_bit_3(void)
{
    REG = REG | 0x8;

}

#define iior(REG) (*(volatile unsigned int *)(REG))
#define iiow(REG, val) (iior(REG) = val)
#define CLEAR_TIME0_IRQ (iiow(TIMER0_REG, (iior(TIMER0_REG) & ~(0x1 << (timer0_flag_pos)))))

void TIMER0_IRQHandler(void)
{
    static volatile int count = 0;
    count++;
    CLEAR_TIME0_IRQ;
    // 請寫一個 Timer 中斷處理函式，每次進來時將 count 加 1
    //     // 並清除中斷旗標（位於某個 fictitious register TIMER0->INTFLAG 的 bit 0）
}
#define US_NOP (asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");)
void delay_ms(unsigned int ms)
{
    int i = 0;
    for (i = 0; i < 1000; i++)
    {
        US_NOP;
    }
        // CPU 頻率 8 MHz，請實作一個大約的 ms 等級 delay function
        //     // 不使用任何 Timer，只用 for-loop delay
}

typedef struct
{
    volatile uint8_t READY;
    volatile uint8_t DATA;
} UART_Registers;

#define UART0 ((UART_Registers *)0x40002000)

uint8_t read_uart_data(void)
{
    volatile UART_Registers* pUartReg = UART0;
    uint8_t data;
    do
    {
        while(!(pUartReg->READY));
            data = pUartReg->DATA;
    } while (!(pUartReg->READY))
    return data;
    // 請寫一個 function，當 UART0->READY 為 1 時才讀取 UART0->DATA
    //     // 並且要確保讀取動作是「原子性」的
}

#define BUF_SIZE 8

typedef struct
{
    //FIFO
    uint8_t buffer[BUF_SIZE];
    uint8_t head; // 寫入位置
    uint8_t tail; // 讀出位置
} CircularBuffer;
extern void cb_init(CircularBuffer* cb);
extern int cb_enqueue(CircularBuffer* cb, uint8_t data);  // 成功回傳 0，滿了回傳 -1
extern int cb_dequeue(CircularBuffer* cb, uint8_t* out);  // 成功回傳 0，空的回傳 -1
void cb_init(CircularBuffer* cb)
{
    //the cb two pointer point same pos, the cube is empty.
    //Since we have 9 condtion but pointer only 8 cond
    //So we delete one condtion
    cb->head = 0;
    cb->tail = 0;
    int idx = 0;
    for (idx = 0; idx < BUF_SIZE; idx++)
    {
        cb->buffer[idx] = 0;
    }
}

int IsEmptyCb(CircularBuffer* cb)
{
    int ret = ((cb->tail) == (cb->head)) ? -1: 0;
    return ret;
}

int IsFullCb(CircularBuffer* cb)
{
    int ret = 0;
    int emptyIdx = cb->head;
    emptyIdx = (emptyIdx + 1) & 0x7;
    ret = (emptyIdx == cb->tail) ? -1 : 0;
}

int cb_enqueue(CircularBuffer* cb, uint8_t data)
{
    int ret = IsFullCb(cb);
    if (-1 != ret)
    {
        int idx = cb->head;
        cb->buffer[idx] = data;
        cb->head = (cb->head + 1) & 0x7;
    }

    return ret;
}

int cb_dequeue(CircularBuffer* cb, uint8_t* out)
{
    int ret = IsEmptyCb(cb);

    if (-1 != ret)
    {
        int idx = cb->tail;
        out = cb->buffer[idx];
        cb->tail = (cb->tail + 1) & 0x7;

    }

    return ret;
}

#define iior(REG)  (*((volatile unsigned int *) (REG)))
#define iiow(REG, val) (iior(REG) = val)
#define SET_GPIO_PIN(PORT, PIN) (iiow(PORT, iior(PORT) | (0x1 << PIN)))

#define MASK_REG 0x90005040
#define 1US_NOP (_asm_volatile ("nop");_asm_volatile ("nop"); _asm_volatile ("nop"); _asm_volatile ("nop"); _asm_volatile ("nop"); _asm_volatile ("nop"); _asm_volatile ("nop");_asm_volatile ("nop");)

int wait_for_flag(volatile uint32_t* reg, uint8_t bit_pos, int timeout_us)
{
    int using_flag = iior(MASK_REG);
    iiow(MASK_REG, 0x0);
    int idx = 0;
    for (idx= 0; idx < timeout_us; idx++)
    {
        1US_NOP;
    }

    int ret = (iior(reg) & 0x1 << (bit_pos)) ? 0 : 1;

    iiow(MASK_REG, using_flag);

    return ret;

}

void memcpyEasy(void *desc, const void *scr, size_t n)
{
    unsigned char *pDesc = (unsigned char *)desc;
    unsigned char *pSrc  = (unsigned char *)src;
    int idx = 0;

    for (idx = 0; idx < n; idx++)
    {
        *pDesc++ = *pSrc++;
    }
}

void memcpyLast(void *desc, const void *scr, size_t n)
{
    unsigned  int *pDescInt  = (unsigned int *)desc;
    unsigned  int *pSrcInt   = (unsigned int *)src;
    unsigned char *pDescChar = NULL;
    unsigned char *pSrcChar  = NULL;

    int quot = n >> 2;
    int rem  = n & 0x3;
    int idx = 0;


    if (0 == ((src | desc) & 0x3))
    {
        for (idx = 0; idx < quot; idx++)
        {
            *pDescInt++ = *pSrcInt++;
        }
        pDescChar = (unsigned char *)pDescInt;
        pSrcChar  = (unsigned char *)pSrcInt;

        for (idx = 0; idx < rem; idx++)
        {
            *pDescChar++ =*pSrcChar++;
        }

    }
    else
    {
        pDescChar = (unsigned char *)desc;
        pSrcChar  = (unsigned char *)src;

        for (idx = 0; idx < n; idx++)
        {
            *pDescChar++ =*pSrcChar++;
        }

    }
}
#define CAN_WRITE_MEM 0x90004000
#define iior(REG) (* ((unsigned int *) (REG)))
#define iiow(REG, val) (iior(REG) = (val))

int findLittleOrBigInMcu(void)
{
    unsigned int val = 0x12345678;
    // 0x1 : little, 0x0 : Big
    int checkFlag = 0x0;
    iiow(CAN_WRITE_MEM, val);//  Can using directly to determine val by pChar
    unsigned char * pChar = (unsigned char*)(CAN_WRITE_MEM);
    checkFlag = (*pChar == 0x78) ? 0x1 : 0x0;

    return checkFlag;
}

uint32_t swap32(uint32_t val)
{
    // the purpose is 32 integer from little to big
    // 32bit = 4byte;
    int n = (4 >> 1);
    int idx = 0;
    unsigned char *pChar = &val;
    unsigned char temp = 0;
    for (idx = 0; idx < n; idx++)
    {
        temp         = pChar[idx];
        pChar[idx]   = pChar[3-idx];
        pChar[3-idx] = temp;

    }

    return val;
    return ((((val >> 24) & 0xf) << 0) | (((val >> 16) & 0xf) << 8) | (((val >> 8) & 0xf) << 16) | ((val & 0xf) << 24))
}


typedef struct UART_FORMAT_T
{
    unsigned char header;
    unsigned int  data;
    unsigned char crc;
}UART_FORMAT_T;

unsigned int ParserUartFormat(unsigned char *pUartStartReg)
{
    while (0xAA == *pUartStartReg)
    {
        //Regestier is Big. // load it by little but it original is big
        unsigned int val = (*(unsigned int *)(pUartStartReg+1));
        unsigned char crc = *(pUartStartReg+5);
        val = swap32(val);
        int idx = 0;
        unsigned char calCrc = (val & 0xf);
        for (idx = 1; idx < 4; idx++)
        {
            calCrc = (((val >> (8 * idx)) & 0xff) ^ calCrc);
        }

        if (calCrc != crc)
        {
            printf("uart is miss or error\n");
        }

    }

    return val;
}


int findSquare(int val)
{
    //1 ..... 45
    int left  = 0;
    int right = 45;
    int currentIdx;

    while (left  != right)
    {
        currentIdx = (left + right) >> 1;
        if ((currentIdx* currentIdx) > val)
        {
            right = currentIdx;
        }
        else if ((currentIdx* currentIdx) < val)
        {
            left = ++currentIdx;
        }
        else
        {
            return currentIdx;
        }

    }

    return currentIdx;
}

#define REG_I2C_SLAVE_VOLTAGE 0x90004000
#define iior(REG) (* ((volatile unsigned int *) (REG)))
#define iiow(REG, val) (iior(REG) = (val))
#define POS_I2C_SDA_VOL 7
#define NOP_1MS

int checkI2CBusForSDA(void)
{
    int count = 0;
    while (!((iior(REG_I2C_SLAVE_VOLTAGE) >> 7) & 0x1))
    {
        NOP_1MS;
        count++;
        if (1000 == count) break;

    }

    return ((iior(REG_I2C_SLAVE_VOLTAGE) >> 7) & 0x1);
}
/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     struct ListNode *next;
 *      * };
 *       */
struct ListNode* reverseList(struct ListNode* head)
{
    P_LIST_NODE_T pNewList = head;
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

int main(void)
{
    const int num = 5;
    int array[] = {4, 1, 3, 5, 2};
    P_LIST_NODE_T pHead  = NULL;//= malloc(sizeof(LIST_NODE_T));
    P_LIST_NODE_T pNext = pHead;
    //int i = 0;
    //for (i = 0; i < num; i++)
    //{
    //    pNext->val = array[i];
    //    pNext->next = ((num-1) == i) ? NULL : malloc(sizeof(LIST_NODE_T));
    //    pNext = pNext->next;
    //}


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






   return 0;
}
