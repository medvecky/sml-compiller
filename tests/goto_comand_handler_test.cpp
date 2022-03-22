#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

extern "C"
{
#include <goto_command_handler.h>
}

TEST_GROUP(GOTO_COMMAND)
{
    static const int STRING_LENGTH = 1024;
    static const int RAM_SIZE = 100;
    char argLine[STRING_LENGTH];
    SymbolTable symbolTable;
    Counters counters;
    SmlArray sml;
    int flags[RAM_SIZE] = {-1};

    void setup() override
    {
        memset(argLine, 0, sizeof(argLine));
        symbolTable.entryCounter = 0;
        memset(symbolTable.entries, 0 , sizeof(symbolTable.entries));
        counters.instructionCounter = 0;
        counters.dataCounter = 99;
        sml.commandCounter = 0;
        memset(sml.commads, 0, sizeof(sml.commads));
        memset(flags, -1, sizeof flags);
    }

    void teardown() override
    {
    }
};

TEST(GOTO_COMMAND, not_exist_in_symbol_table)
{
    std::strcpy(argLine, "50");
    CHECK(gotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(1, SmlArray_getCounter(&sml));
    CHECK_EQUAL(4000, SmlArray_getCommand(&sml, 0));
}

TEST(GOTO_COMMAND, exist_in_symbol_table)
{
    std::strcpy(argLine, "50");
    SymbolTable_set(
            &symbolTable,
            50,
            LINE, 
            99); 
    CHECK(gotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(1, SmlArray_getCounter(&sml));
    CHECK_EQUAL(4099, SmlArray_getCommand(&sml, 0));
}

TEST(GOTO_COMMAND, not_a_number)
{
    std::strcpy(argLine, "dd");
    CHECK_FALSE(gotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
}
