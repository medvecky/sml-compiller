#ifndef _LET_COMMAND_HANDLER_H
#define _LET_COMMAND_HANDLER_H

#include <stdbool.h>
#include "symbol_table.h"
#include "counters.h"
#include "postfix_evaluator.h"

bool letCommandHandler(
        char * argLine,
        SymbolTable * symbolTable,
        Counters * counters,
        PostfixEntry * postfix,
        SmlArray * sml);

#endif
