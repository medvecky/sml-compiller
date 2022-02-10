#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "modules/to_postfix_converter.h"
#include "modules/postfix_evaluator.h"

#define STRING_LENGTH   1024

int main()
{
    char infixString[STRING_LENGTH] = {'\0'};
    PostfixEntry postfixString[STRING_LENGTH];

    puts("Enter infix string");
    fgets(infixString, STRING_LENGTH, stdin);

    int lineLength  = convertToPostfix(infixString, postfixString); 

    if (lineLength == -1)
    {
        puts("convertToPostfix: ERROR");
        return EXIT_FAILURE;
    } // end if 

    for (int index = 0; index < lineLength; index++)
    {
        printf("Entry %d: ", index);
       if (postfixString[index].type == CONSTANT)
       {
           printf("type constant, value: %d\n", postfixString[index].item);
       } // end if
       else if (postfixString[index].type == OPERATOR)
       {
           printf("type operator, value: %c\n", postfixString[index].item);
       } // end else if
       else
       {
           printf("type variable, value: %c\n", postfixString[index].item);
       } // end else
    }

    puts("End of program.");
    return EXIT_SUCCESS;
} // end main
