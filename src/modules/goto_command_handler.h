#ifndef _GOTO_COMMAND_HANDLER_H_
#define _GOTO_COMMAND_HANDLER_H_

#include <stdbool.h>
#include "symbol_table.h"
#include "sml_array.h"
#include "counters.h"

bool gotoCommandHandler(
        char * argLine,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml,
        int * flags);

#endif
