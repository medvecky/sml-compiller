#include <stdlib.h>
#include <ctype.h>
#include "counters.h"
#include "if_goto_command_handler.h"
#include "helpers.h"
#include "commands.h"
#include "sml_array.h"
#include "symbol_table.h"

static bool branchZeroHandler(
        char operand1,
        char operand2,
        int targetLocation,
        int targetLineNumber,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml,
        int * flags);

static bool branchNegHandler(
        char operand1,
        char operand2,
        char equalityOperation,
        int targetLocation,
        int targetLineNumber,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml,
        int * flags);

bool ifGotoCommandHandler(
        char * argLine,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml,
        int * flags)
{
    char operand1 = argLine[0];
    char equalityOperation = argLine[2];
    char operand2 = argLine[4];
    int targetLineNumber = atoi(argLine + 11); 
    int targetLocation = SymbolTable_findLocation(symbolTable, targetLineNumber, LINE);

    if (equalityOperation == '=')
    {
        if (!branchZeroHandler(
                    operand1,
                    operand2,
                    targetLocation,
                    targetLineNumber,
                    symbolTable, 
                    counters,
                    sml,
                    flags))
        {
            return false;
        } // end if error in branchZeroHandler
    } // end if =
    else if (equalityOperation == '<' || equalityOperation == '>')
    {
        if (!branchNegHandler(
                    operand1,
                    operand2,
                    equalityOperation,
                    targetLocation,
                    targetLineNumber,
                    symbolTable, 
                    counters,
                    sml,
                    flags))
        {
            return false;
        } // end if error in branchZeroHandler
    } // end else if < >
    else
    {
        return false;
    } // end else wrong equalityOperation
    return true;
} // end function ifGotoCommandHandler

static bool branchZeroHandler(
        char operand1,
        char operand2,
        int targetLocation,
        int targetLineNumber,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml,
        int * flags)
{
    int operand1Location = getOrSetVariableLocaton(operand1, symbolTable, counters);
    if (operand1Location == -1)
        return false;
    
    if (operand2 == '0')
    {
        if (!SmlArray_addCommand(sml, LOAD * 100 + operand1Location) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);
    } // end of if operand2 == 0
    else 
    {
        if (!isalpha(operand2))
        {
            return false;
        } // end if operand2 not a variable
        
        int operand2Location = getOrSetVariableLocaton(operand2, symbolTable, counters);
        if (operand2Location == -1)
            return  false;
        
        if (!SmlArray_addCommand(sml, LOAD * 100 + operand1Location) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);
        
        if (!SmlArray_addCommand(sml, SUBSTRACT * 100 + operand2Location) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);
        
    } // end else operand2 != 0
    
    if (targetLocation == -1)
    {
        flags[Counters_getInstructionCounter(counters)] = targetLineNumber;
        targetLocation = 0;
    } // end if targetLocation not in symbol table
    
    if (!SmlArray_addCommand(sml, BRANCHZERO * 100 + targetLocation) || 
            Counters_getInstructionCounter(counters) == -1)
    {
        return false;
    }
    Counters_incrementInstructionCounter(counters);
    
    return true;
} // end function branchZeroHandler

static bool branchNegHandler(
        char operand1,
        char operand2,
        char equalityOperation,
        int targetLocation,
        int targetLineNumber,
        SymbolTable * symbolTable,
        Counters * counters,
        SmlArray * sml,
        int * flags)
{
    int operand1Location = getOrSetVariableLocaton(operand1, symbolTable, counters);
    if (operand1Location == -1)
        return false;

    int operand2Location = getOrSetVariableLocaton(operand2, symbolTable, counters);
    if (operand2Location == -1)
        return false;

    if (equalityOperation == '<')
    {
        if (!SmlArray_addCommand(sml, LOAD * 100 + operand1Location) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);
        
        if (!SmlArray_addCommand(sml, SUBSTRACT * 100 + operand2Location) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);
    } // end if <  
    else
    {
        if (!SmlArray_addCommand(sml, LOAD * 100 + operand2Location) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);
        
        if (!SmlArray_addCommand(sml, SUBSTRACT * 100 + operand1Location) || 
                Counters_getInstructionCounter(counters) == -1)
        {
            return false;
        }
        Counters_incrementInstructionCounter(counters);

    } // end else > 
    if (targetLocation == -1)
    {
        flags[Counters_getInstructionCounter(counters)] = targetLineNumber;
        targetLocation = 0;
    } // end if targetLocation not in symbol table
    
    if (!SmlArray_addCommand(sml, BRANCHNEG * 100 + targetLocation) || 
            Counters_getInstructionCounter(counters) == -1)
    {
        return false;
    }
    Counters_incrementInstructionCounter(counters);
    
    return true;
} // end function branchNegHandler
