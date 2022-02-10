#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "to_postfix_converter.h"
#include "stack.h"

static int getOperatorValue(char operator);
static bool isNumber(char * string);
static bool isVariable(char * string);

/* the function converts input infix string to postfix view
   arguments: a pointer to infix string, a pointer to PostfixEntry array
   return value - number of converted tokens or -1 as an error
*/
int convertToPostfix(char infix[], PostfixEntry postfix[])
{
    StackNodePtr stackPtr = NULL;
    size_t infixCounter = 0;
    size_t postfixCounter = 0;
    char character;

    Stack_push(&stackPtr, '(');
    while ((character = infix[infixCounter++]) != '\n')
        ;
    infix[--infixCounter] = ' ';
    infix[++infixCounter] = ')';
    infix[++infixCounter] = '\0';
    infixCounter = 0;
    
    char * token = strtok(infix, " ");
    while (!Stack_isEmpty(stackPtr) && token != NULL) 
    {
        if (isNumber(token))
        {
            postfix[postfixCounter].item = atoi(token);
            postfix[postfixCounter++].type = CONSTANT;
        } // end if
        else if (isVariable(token))
        {
            postfix[postfixCounter].item = token[0]; 
            postfix[postfixCounter++].type = VARIABLE;
        } // end else if
        else if (strlen(token) == 1 && token[0] == '(')
        {
            Stack_push(&stackPtr, token[0]);
        } // end else if
        else if (strlen(token) == 1 && isOperator(token[0]))
        {
            char operator;
            char currentCharacter = token[0];
            while (isOperator(operator = Stack_getTop(stackPtr)))
            { 
                if (precedence(operator, currentCharacter) >= 0)
                {       
                    postfix[postfixCounter].item = operator;
                    postfix[postfixCounter++].type = OPERATOR;
                    Stack_pop(&stackPtr);
                } // end if
                else
                {
                    break;
                }
            } // end while
            Stack_push(&stackPtr, currentCharacter);
        } // end else if
        else if (strlen(token) == 1 && token[0] == ')')
        {
            char operator;
            while (isOperator(operator = Stack_getTop(stackPtr)))
            {
                postfix[postfixCounter].item = operator;
                postfix[postfixCounter++].type = OPERATOR;
                Stack_pop(&stackPtr);
            } // end while
            
            Stack_pop(&stackPtr);
        } // end else if
        else
        {
            return -1;
        } // end else
        token = strtok(NULL, " ");
    } // end while
   
    return postfixCounter;
} // end function convertToPostfix

bool isOperator(char c)
{
    switch (c)
    {
        case '+' :
        case '-' :
        case '*' :
        case '/' :
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
            return 2;
        default:
            return 0;
    } // end switch

} // end function getOperatorValue

static bool isNumber(char * string)
{
     while (*string) {
        if (isdigit(*string++) == 0) return false;
    }

    return true;
} // end function isNumber

static bool isVariable(char * string)
{
    return strlen(string) == 1 && isalpha(string[0]);
} // end function isVariable
