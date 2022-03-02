#include "helpers.h"

int getOrSetVariableLocaton(char variable, SymbolTable * symbolTable, Counters * counters)
{
    int locaton = SymbolTable_findLocation(symbolTable, variable, VARIABLE);
    if (locaton == -1)
    {
        locaton = Counters_getDataCounter(counters);
        if (locaton == -1)
            return -1;

        Counters_incrementDataCounter(counters);
                  
        if (!SymbolTable_set(symbolTable, variable, VARIABLE, locaton))
            return -1; 
    } // end if
    return locaton;
} // end function getOrSetVariableLocaton
