#include "goto_command_handler.h"
#include "commands.h"
#include <stdlib.h>

bool gotoCommandHandler(
        char * argLine,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml,
        int * flags)
{
    int targetLineNumber = atoi(argLine);
    int targetLocation = SymbolTable_findLocation(symbolTable, targetLineNumber, LINE);
    if (targetLocation == -1)
    {
        flags[Counters_getInstructionCounter(counters)] = targetLineNumber;
        if (!SmlArray_addCommand(sml, BRANCH * 100 ) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);
    } // end if line does not exist in symbolTable
    else
    {
        if (!SmlArray_addCommand(sml, BRANCH * 100 + targetLocation) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);
    } // end else line exists in symbolTable
    return true;
} // end function gotoCommandHandler
