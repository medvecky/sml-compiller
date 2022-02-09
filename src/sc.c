#include <stdio.h>
#include <stdlib.h>
#include "modules/to_postfix_converter.h"
#include "modules/postfix_evaluator.h"

#define STRING_LENGTH   1024

int main()
{
    char infixString[STRING_LENGTH] = {'\0'};
    char postfixString[STRING_LENGTH] = {'\0'};

    puts("Enter infix string");
    fgets(infixString, STRING_LENGTH, stdin);

    convertToPostfix(infixString, postfixString); 

    printf("Postfix string: %s\n", postfixString);

    int result = evaluatePostfixExpression(postfixString);

    printf("Result is: %d\n", result);

    puts("End of program.");
    return EXIT_SUCCESS;
} // end main
