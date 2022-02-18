#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "postfix_evaluator.h"
#include "sml_array.h"
#include "stack.h"
#include "symbol_table.h"
#include "to_postfix_converter.h"
#include "counters.h"

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
                return -1;
            } // end if
            else if (location == -1)
            {
                location = Counters_getDataCounter(counters);
                Counters_incrementDataCounter(counters);
                if (location == -1)
                    return -1;
                if (!SymbolTable_set(symbolTable, postfix[index].item, type, location))
                    return -1;
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

int calculate(
        size_t op1, 
        size_t op2,
        char operation,
        Counters * counters,
        SmlArray * sml)
{
    int tempLocation;
    switch(operation)
    {
        case '+':
            if (!SmlArray_addCommand(sml, 20 * 100 + op1)) return -1; 
            if (!SmlArray_addCommand(sml, 30 * 100 + op2)) return -1;
            if ((tempLocation = Counters_getDataCounter(counters)) == -1) return -1;
            Counters_incrementDataCounter(counters);
            if (!SmlArray_addCommand(sml, 21 * 100 + tempLocation)) return -1;
            return tempLocation;
        case '-': 
            if (!SmlArray_addCommand(sml, 20 * 100 + op1)) return -1; 
            if (!SmlArray_addCommand(sml, 31 * 100 + op2)) return -1;
            if ((tempLocation = Counters_getDataCounter(counters)) == -1) return -1;
            Counters_incrementDataCounter(counters);
            if (!SmlArray_addCommand(sml, 21 * 100 + tempLocation)) return -1;
            return tempLocation;
        case '*':
            if (!SmlArray_addCommand(sml, 20 * 100 + op1)) return -1; 
            if (!SmlArray_addCommand(sml, 33 * 100 + op2)) return -1;
            if ((tempLocation = Counters_getDataCounter(counters)) == -1) return -1;
            Counters_incrementDataCounter(counters);
            if (!SmlArray_addCommand(sml, 21 * 100 + tempLocation)) return -1;
            return tempLocation;
        case '/':
            if (!SmlArray_addCommand(sml, 20 * 100 + op1)) return -1; 
            if (!SmlArray_addCommand(sml, 32 * 100 + op2)) return -1;
            if ((tempLocation = Counters_getDataCounter(counters)) == -1) return -1;
            Counters_incrementDataCounter(counters);
            if (!SmlArray_addCommand(sml, 21 * 100 + tempLocation)) return -1;
            return tempLocation;
        default:
            puts("calculate: illegal opertion");
            return -1;
    } // end switch
} // end function calculate
