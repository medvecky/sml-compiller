#ifndef TO_POSTFIX_CONVERTER_H
#define TO_POSTFIX_CONVERTER_H

#include <stdbool.h>
#include <stdio.h>
enum postfixEntryType {CONST, VAR, OPERATOR};
typedef enum postfixEntryType PostfixEntryType;

struct postfixEntry
{
    int item;
    PostfixEntryType type;
};
typedef struct postfixEntry PostfixEntry;

int convertToPostfix(char infix[], PostfixEntry postfix[]);
bool isOperator(char c);
int precedence (char operator1, char operator2);

#endif
