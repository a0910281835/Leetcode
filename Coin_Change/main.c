#include "stdio.h"
#include "stdlib.h"

#define ERROR -1

int coinChange(int* coins, int coinsSize, int amount)
{
    //Inital Conditon
    if (amount == 0) return 0;
    if (coinsSize == 0)
    {
        if (0 == amount) return 0;
        else             return -1;
    }


    //The MAX coin  is coins[coinSize-1];
    int maxCoin = coins[coinsSize-1];
    int maxCnt  = amount / maxCoin;
    int restMony;

    int idx = maxCnt;
    int recordUseSmallest = 100000;

    printf("-----Start------\n");
    printf("amount : %2d\n,", amount);

    for (idx = 0; idx < coinsSize; idx++)
    {
        printf("%2d,", coins[idx]);
    }
    printf("-----End------\n");

    for (idx = maxCnt; idx >= 0; idx--)
    {
        restMony = amount - (maxCoin * idx);
        int ret = coinChange(coins, coinsSize - 1, restMony);


        if (ERROR != ret) ret += idx;
        else continue;

        if (recordUseSmallest > ret) recordUseSmallest = ret;
    }

    if (recordUseSmallest == 100000) recordUseSmallest = ERROR;

    return recordUseSmallest;

}
int main(void)
{

    int coins[3] = {1, 2, 5};
    int size = 3;
    int amount = 13;

    int ret = coinChange(coins, size, amount);
    printf("%2d\n", ret);

    return 1;
}
