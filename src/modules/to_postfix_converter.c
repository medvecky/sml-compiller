#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include "to_postfix_converter.h"
#include "stack.h"

static int getOperatorValue(char operator);

void convertToPostfix(char infix[], char postfix[])
{
    StackNodePtr stackPtr = NULL;
    size_t infixCounter = 0;
    size_t postfixCounter = 0;
    char currentCharacter;

    Stack_push(&stackPtr, '(');
    while ((currentCharacter = infix[infixCounter++]) != '\n')
        ;
    infix[--infixCounter] = ')';
    infix[++infixCounter] = '\0';
    infixCounter = 0;

    while (!Stack_isEmpty(stackPtr) &&
            (currentCharacter = infix[infixCounter++]) != '\0')
    {
        if (isdigit(currentCharacter))
        {
            postfix[postfixCounter++] = currentCharacter;
        } // end if
        else if (currentCharacter == '(')
        {
            Stack_push(&stackPtr, currentCharacter);
        } // end else if
        else if (isOperator(currentCharacter))
        {
            char operator;
            while (isOperator(operator = Stack_getTop(stackPtr)))
            { 
                if (precedence(operator, currentCharacter) >= 0)
                {       
                    postfix[postfixCounter++] = operator;
                    Stack_pop(&stackPtr);
                } // end if
                else
                {
                    break;
                }
            } // end while
            Stack_push(&stackPtr, currentCharacter);
        } // end else if
        else if (currentCharacter == ')')
        {
            char operator;
            while (isOperator(operator = Stack_getTop(stackPtr)))
            {
                postfix[postfixCounter++] = operator;
                Stack_pop(&stackPtr);
            } // end while
            
            Stack_pop(&stackPtr);
        } // end else if
    } // end while

    puts("End of convertToPostfix");
} // end function convertToPostfix

bool isOperator(char c)
{
    switch (c)
    {
        case '+' :
        case '-' :
        case '*' :
        case '/' :
        case '%' :
        case '^' :
            return true;
        default:
            return false;
    }
} // end function isOperator

/* The function determines operators precedence */
int precedence (char operator1, char operator2)
{
    int difference = 
        getOperatorValue(operator1) - getOperatorValue(operator2);

    if (difference > 0)
        return 1;
    if (difference < 0)
        return -1;
    return 0;
} // end function precedence

/* The function returns operator precedence value
 * or 0 as an error value.
 */
static int getOperatorValue(char operator)
{
    switch (operator)
    {
        
        case '+' :
        case '-' :
            return 1;
        case '*' :
        case '/' :
        case '%' :
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    } // end switch

} // end function getOperatorValue
