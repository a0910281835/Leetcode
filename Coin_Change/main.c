#include "stdio.h"
#include "stdlib.h"

#define ERROR -1

// Use Recursive but efficiency is bad
// Since High to Low
 /*
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
*/
// Version : Consumes Space.
int coinChange(int* coins, int coinsSize, int amount)
{
    //Dymaic Progamming
    int totalMoney = 0;
    int recordSmallestNumForThisAmount[amount + 1];

    //inital Condition
    recordSmallestNumForThisAmount[0] = 0;

    for (totalMoney = 1; totalMoney <= amount; totalMoney++)
    {
        int tempMin = 10001;// amount <= 10000
        int idx = 0;

        for (idx = 0; idx < coinsSize; idx++)
        {
            int dividMoney = (totalMoney - coins[idx]);


            if (dividMoney < 0 || (recordSmallestNumForThisAmount[dividMoney] == -1))
                continue;
            else
            {
                tempMin = (tempMin > (1 + recordSmallestNumForThisAmount[dividMoney])) ? (1 + recordSmallestNumForThisAmount[dividMoney]) : tempMin;
            }

        }

        if (tempMin == 10001) recordSmallestNumForThisAmount[totalMoney] = -1;
        else                  recordSmallestNumForThisAmount[totalMoney] = tempMin;

    }

    return  recordSmallestNumForThisAmount[amount];
}

int main(void)
{

    int coins[3] = {1, 2, 5};
    int size = 3;
    int amount = 15;

    int ret = coinChange(coins, size, amount);
    printf("Use : %2d\n", ret);

    return 1;
}
