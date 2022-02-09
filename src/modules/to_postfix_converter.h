#ifndef TO_POSTFIX_CONVERTER_H
#define TO_POSTFIX_CONVERTER_H

#include <stdbool.h>

enum postfixEntryType {CONSTANT, VARIABLE, OPERATOR};
typedef enum postfixEntryType PostfixEntryType;

struct postfixEntry
{
    int item;
    PostfixEntryType type;
};
typedef struct postfixEntry PostfixEntry;

void convertToPostfix(char infix[], PostfixEntry postfix[]);
bool isOperator(char c);
int precedence (char operator1, char operator2);

#endif
