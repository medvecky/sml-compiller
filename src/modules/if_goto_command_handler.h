#ifndef _IF_GOTO_COMMAND_HANDLER_H_
#define _IF_GOTO_COMMAND_HANDLER_H_

#include <stdbool.h>
#include "symbol_table.h"
#include "counters.h"
#include "sml_array.h"

bool ifGotoCommandHandler(
        char * argLine,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml,
        int * flags);

#endif
