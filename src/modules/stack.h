#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// self-referential structure                     
struct stackNode 
{                                   
    int data; // define data as an int             
    struct stackNode *nextPtr; // stackNode pointer
}; // end structure stackNode                     

typedef struct stackNode StackNode; // synonym for struct stackNode
typedef StackNode *StackNodePtr; // synonym for StackNode*

// prototypes
void Stack_push(StackNodePtr * topPtr, int value);
int Stack_pop(StackNodePtr * topPtr);
bool Stack_isEmpty(StackNodePtr topPtr);
void Stack_print( StackNodePtr currentPtr);
int Stack_getTop(StackNodePtr topPtr);

#endif
