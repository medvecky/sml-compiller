#include <string.h>
#include "let_command_hadnler.h"
#include "commands.h" 
#include "helpers.h"

bool letCommandHandler(
        char * argLine,
        SymbolTable * symbolTable,
        Counters * counters,
        PostfixEntry * postfix,
        SmlArray * sml)
{
    size_t argLineLength = strlen(argLine);
            
    char op1 = argLine[0];
    int op1Locaton = getOrSetVariableLocaton(op1, symbolTable, counters);
    if (op1Locaton == -1)
        return false;
            
    int op2Locaton = 0;

    if (argLineLength == 6)
    {
        char op2 = argLine[4]; 
        op2Locaton = getOrSetVariableLocaton(op2, symbolTable, counters);
    } // end if
    else if (argLineLength > 6)
    {
        char * infixLine = argLine + 4;
        size_t postfixSize = convertToPostfix(infixLine, postfix);
        op2Locaton = evaluatePostfixExpression(
                postfix,
                postfixSize,
                symbolTable,
                counters,
                sml);
    } // end  else if
    else
    {   
        return false;
    } // end else        
    
    if (op2Locaton == -1)
        return false;

    if (!SmlArray_addCommand(sml, LOAD * 100 + op2Locaton) || 
            Counters_getInstructionCounter(counters) == -1) 
        return false; 
    Counters_incrementInstructionCounter(counters);
                
    if (!SmlArray_addCommand(sml, STORE * 100 + op1Locaton) || 
            Counters_getInstructionCounter(counters) == -1) 
        return false; 
    Counters_incrementInstructionCounter(counters);
    
    return true;
} // end function letCommandHandler
