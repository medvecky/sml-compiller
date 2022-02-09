#ifndef TO_POSTFIX_CONVERTER_H
#define TO_POSTFIX_CONVERTER_H

#include <stdbool.h>
void convertToPostfix(char infix[], char postfix[]);
bool isOperator(char c);
int precedence (char operator1, char operator2);

#endif
