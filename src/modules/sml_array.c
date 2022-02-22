#include "sml_array.h"
#include <stdbool.h>

size_t SmlArray_getCounter(SmlArray * smlArray)
{
    return smlArray->commandCounter;
} // end function SmlArray_getCounter

bool SmlArray_addCommand(SmlArray * smlArray, int command)
{
    if (smlArray->commandCounter >= SML_ARRAY_SIZE)
        return false;
    
    smlArray->commads[smlArray->commandCounter++] = command;
    
    return true;
} // end function SmlArray_addCommand

bool SmlArray_editCommand(SmlArray * smlArray, size_t commandNumber, int command)
{
   if (commandNumber < 0 || commandNumber >= smlArray->commandCounter)
       return false;

   smlArray->commads[commandNumber] = command;

   return true;
} // end function SmlArray_editCommand

int SmlArray_getCommand(SmlArray * smlArray, size_t commandNumber)
{
   if (commandNumber < 0 || commandNumber >= smlArray->commandCounter)
       return -1;

   return smlArray->commads[commandNumber];
} // end function SmlArray_getCommand
