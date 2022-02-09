#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "postfix_evaluator.h"
#include "stack.h"

int evaluatePostfixExpression(char * expression)
{
    char character;
    size_t stringCounter = 0;
    StackNodePtr stackPtr = NULL;
    while((character = expression[stringCounter++]) != '\0')
    {
        if (isdigit(character))
        {
            Stack_push(&stackPtr, character - '0');
        } // end if 
        else
        {
            int x = Stack_pop(&stackPtr);
            int y = Stack_pop(&stackPtr);
            Stack_push(&stackPtr, calculate(y, x, character));
        }
    } // end while
    
    return Stack_pop(&stackPtr);
} // end function evaluatePostfixExpression

int calculate(int op1, int op2, char operation)
{
    switch(operation)
    {
        case '+':
            return op1 + op2;
        case '-': 
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
        case '%':
            return op1 % op2;
        case '^':
            return pow(op1, op2);
        default:
            puts("calculate: illegal opertion");
            return -1;
    } // end switch
} // end function calculate
