#ifndef POSTFIX_EVALUATOR_H
#define POSTFIX_EVALUATOR_H

#include <stdbool.h>
#include "counters.h"
#include "to_postfix_converter.h"
#include "sml_array.h"
#include "symbol_table.h"

int evaluatePostfixExpression(
        PostfixEntry * postfix, 
        size_t postfixSize,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml);
int calculate(
        size_t op1, 
        size_t op2,
        char operation, 
        Counters * counters,
        SmlArray * sml);

#endif
