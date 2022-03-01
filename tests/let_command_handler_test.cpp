#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

extern "C"
{
#include <let_command_hadnler.h>
}

TEST_GROUP(REM_COMMAND)
{
    static const int STRING_LENGTH = 1024;
    SymbolTable symbolTable;
    Counters counters;
    PostfixEntry postfix[STRING_LENGTH]; 
    SmlArray sml;
    char argLine[STRING_LENGTH];
    
    void setup() override
    {
        memset(argLine, 0, sizeof(argLine));
        memset(postfix, 0, sizeof(postfix));
        sml.commandCounter = 0;
        memset(sml.commads, 0, sizeof(sml.commads));
        symbolTable.entryCounter = 0;
        memset(symbolTable.entries, 0 , sizeof(symbolTable.entries));
        counters.instructionCounter = 0;
        counters.dataCounter = 99;
    }

    void teardown() override
    {
    }
};

TEST(REM_COMMAND, simple_good)
{
    std::strcpy(argLine, "x = y\n");
    CHECK(letCommandHandler(
                argLine,
                &symbolTable, 
                &counters,
                postfix, 
                &sml));
}
