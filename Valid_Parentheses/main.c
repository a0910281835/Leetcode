 /** 20. Valid Parentheses
  *
  *
  * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
  *
  * An input string is valid if:
  *
  * Open brackets must be closed by the same type of brackets.
  * Open brackets must be closed in the correct order.
  * Every close bracket has a corresponding open bracket of the same type.
  *
  *
  *
  *
  * Example 1:
  *
  * Input: s = "()"
  * Output: true
 **/
#include "stdio.h"
#include"stdlib.h"
#define MAX_SIZE 1000

typedef unsigned char bool;

typedef struct STACK_CHAR_t * P_STACK_CHAR_t;

typedef struct STACK_CHAR_t
{
    char array[MAX_SIZE];
    int current_num;

}STACK_CHAR_t;

bool isValid(char * s)
{


}

int main(void)
{
    return 1;

}
