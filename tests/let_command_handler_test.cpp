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
    CHECK_EQUAL(2, SymbolTable_getEntryCount(&symbolTable));
    CHECK_EQUAL('x', SymbolTable_getEntry(&symbolTable, 0)->symbol);
    CHECK_EQUAL(99, SymbolTable_getEntry(&symbolTable, 0)->location);
    CHECK_EQUAL(VARIABLE, SymbolTable_getEntry(&symbolTable, 0)->type);
    CHECK_EQUAL('y', SymbolTable_getEntry(&symbolTable, 1)->symbol);
    CHECK_EQUAL(98, SymbolTable_getEntry(&symbolTable, 1)->location);
    CHECK_EQUAL(VARIABLE, SymbolTable_getEntry(&symbolTable, 1)->type);
    CHECK_EQUAL(2, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2098, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(2199, SmlArray_getCommand(&sml, 1));
}

TEST(REM_COMMAND, complex_good)
{
    std::strcpy(argLine, "x = y + z\n");
    CHECK(letCommandHandler(
                argLine,
                &symbolTable, 
                &counters,
                postfix, 
                &sml));
    CHECK_EQUAL(3, SymbolTable_getEntryCount(&symbolTable));
    CHECK_EQUAL('x', SymbolTable_getEntry(&symbolTable, 0)->symbol);
    CHECK_EQUAL(99, SymbolTable_getEntry(&symbolTable, 0)->location);
    CHECK_EQUAL(VARIABLE, SymbolTable_getEntry(&symbolTable, 0)->type);
    CHECK_EQUAL('y', SymbolTable_getEntry(&symbolTable, 1)->symbol);
    CHECK_EQUAL(98, SymbolTable_getEntry(&symbolTable, 1)->location);
    CHECK_EQUAL(VARIABLE, SymbolTable_getEntry(&symbolTable, 1)->type);
    CHECK_EQUAL('z', SymbolTable_getEntry(&symbolTable, 2)->symbol);
    CHECK_EQUAL(97, SymbolTable_getEntry(&symbolTable, 2)->location);
    CHECK_EQUAL(VARIABLE, SymbolTable_getEntry(&symbolTable, 2)->type);

    CHECK_EQUAL(5, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2098, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(3097, SmlArray_getCommand(&sml, 1));
    CHECK_EQUAL(2196, SmlArray_getCommand(&sml, 2));
    CHECK_EQUAL(2096, SmlArray_getCommand(&sml, 3));
    CHECK_EQUAL(2199, SmlArray_getCommand(&sml, 4));
}

TEST(REM_COMMAND, bad_arg_string)
{
    std::strcpy(argLine, "x =\n");
    CHECK_FALSE(letCommandHandler(
                argLine,
                &symbolTable, 
                &counters,
                postfix, 
                &sml));
}
