#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void Stack_push(StackNodePtr * topPtr, int value)
{
    StackNodePtr newPtr;

    newPtr = malloc(sizeof(StackNode));
    
    if (newPtr != NULL)
    {
        newPtr->data = value;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } // end if
    else 
    {
        printf("'%c' not inserted. No memory available.\n", value);
    } // end else
} // end function push  

void Stack_print(StackNodePtr currentPtr)
{
    if (currentPtr == NULL)
    {
        puts("The stack is empty");
    } // end if
    else
    {
        puts("The stack is: ");

        while (currentPtr != NULL)
        {
            printf("'%c' --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        } // end while

        puts("NULL\n");
    } // end else
} // end function printStack

int Stack_pop(StackNodePtr * topPtr)
{
    StackNodePtr tempPtr;
    int popValue;

    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);

    return popValue;
} // end function pop

bool Stack_isEmpty(StackNodePtr topPtr)
{
    return topPtr == NULL;
} // end function isEmpty

int Stack_getTop(StackNodePtr topPtr)
{
    return topPtr->data;
} // end function stackTop
