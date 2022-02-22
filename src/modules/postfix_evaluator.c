#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "postfix_evaluator.h"
#include "sml_array.h"
#include "stack.h"
#include "symbol_table.h"
#include "to_postfix_converter.h"
#include "counters.h"
#include "commands.h"

static int generateArithmeticOperationCode(
        size_t op1, 
        size_t op2, 
        int operationCode, 
        Counters * counters, 
        SmlArray * sml);


/* Convert postfix array data to sml code 
 *  argguments:
 *  PostfixEntry - pointer to postfix array
 *  postfixSize - size of postfix array
 *  symbolTable - pointer to SymbolTable
 *  counters - ponter to counters
 *  sml - pointer to sml array
 *
 *  return value - location where stored result of expression
 *  or -1 as error sign
 *
 *  function modifies symbolTable and counters
 *  result sml code stores in sml array
 */
int evaluatePostfixExpression(
        PostfixEntry * postfix, 
        size_t postfixSize,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml)
{
    StackNodePtr stackPtr = NULL;
    for (size_t index = 0; index < postfixSize; index++)
    {
        if (postfix[index].type == VAR || postfix[index].type == CONST)
        {
            TableEntryType type; 
            if (postfix[index].type == VAR)
                type = VARIABLE;
            else 
                type = CONSTANT;

            int location = SymbolTable_findLocation(symbolTable, postfix[index].item, type);
            if (location == -1 && type == CONSTANT)
            {
                Stack_free(&stackPtr);
                return -1;
            } // end if
            else if (location == -1)
            {
                location = Counters_getDataCounter(counters);
                Counters_incrementDataCounter(counters);
                if (location == -1)
                {
                    Stack_free(&stackPtr);
                    return -1;
                } // end if
                if (!SymbolTable_set(symbolTable, postfix[index].item, type, location))
                {
                    Stack_free(&stackPtr);
                    return -1;
                } // end if
            } // end else if
            Stack_push(&stackPtr, location);
        } // end if 
        else
        {
            size_t locationSecond = Stack_pop(&stackPtr);
            size_t locationFirst = Stack_pop(&stackPtr);
            Stack_push(
                    &stackPtr, 
                    calculate(
                        locationFirst, 
                        locationSecond, 
                        postfix[index].item,
                        counters,
                        sml));
        }
    } // end while
    
    return Stack_pop(&stackPtr);
} // end function evaluatePostfixExpression

/*
 * Generates math operation code
 * returns memory location for result
 * or -1 as error
 */
int calculate(
        size_t op1, 
        size_t op2,
        char operation,
        Counters * counters,
        SmlArray * sml)
{
    switch(operation)
    {
        case '+':
            return generateArithmeticOperationCode(op1, op2, ADD, counters, sml);
        case '-': 
            return generateArithmeticOperationCode(op1, op2, SUBSTRACT, counters, sml);
        case '*':
            return generateArithmeticOperationCode(op1, op2, MULTIPLY, counters, sml);
        case '/':
            return generateArithmeticOperationCode(op1, op2, DIVIDE, counters, sml);
        default:
            puts("calculate: illegal opertion");
            return -1;
    } // end switch
} // end function calculate

static int generateArithmeticOperationCode(
        size_t op1, 
        size_t op2, 
        int operationCode, 
        Counters * counters, 
        SmlArray * sml)
{
    int tempLocation;

    if (!SmlArray_addCommand(sml, LOAD * 100 + op1) || 
            Counters_getInstructionCounter(counters) == -1) 
        return -1; 
    Counters_incrementInstructionCounter(counters);
    
    if (!SmlArray_addCommand(sml, operationCode * 100 + op2) ||
            Counters_getInstructionCounter(counters) == -1) 
        return -1;
    Counters_incrementInstructionCounter(counters);
    
    if ((tempLocation = Counters_getDataCounter(counters)) == -1)
        return -1;
    Counters_incrementDataCounter(counters);

    if (!SmlArray_addCommand(sml, STORE * 100 + tempLocation) || 
            Counters_getInstructionCounter(counters) == -1)
        return -1;
    Counters_incrementInstructionCounter(counters);
    
    return tempLocation;
} // end function generateArithmeticOperationCode
