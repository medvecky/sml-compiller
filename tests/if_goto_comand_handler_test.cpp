#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

extern "C"
{
#include <if_goto_command_handler.h>
}

TEST_GROUP(IF_GOTO_COMMAND)
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

TEST(IF_GOTO_COMMAND, equal_zero_line_exist)
{
    std::strcpy(argLine, "x = 0 goto 50");
    SymbolTable_set(
            &symbolTable,
            50,
            LINE, 
            99);
    Counters_incrementDataCounter(&counters);
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(2, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2098, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(4299, SmlArray_getCommand(&sml, 1));
}

TEST(IF_GOTO_COMMAND, equal_zero_line_not_exist)
{
    std::strcpy(argLine, "x = 0 goto 50");
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(2, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2099, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(4200, SmlArray_getCommand(&sml, 1));
}

TEST(IF_GOTO_COMMAND, equal_variable_line_exist)
{
    std::strcpy(argLine, "x = y goto 50");
    SymbolTable_set(
            &symbolTable,
            50,
            LINE, 
            99);
    Counters_incrementDataCounter(&counters);
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(3, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2098, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(3197, SmlArray_getCommand(&sml, 1));
    CHECK_EQUAL(4299, SmlArray_getCommand(&sml, 2));
}

TEST(IF_GOTO_COMMAND, equal_variable_line_not_exist)
{
    std::strcpy(argLine, "x = y goto 50");
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(3, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2099, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(3198, SmlArray_getCommand(&sml, 1));
    CHECK_EQUAL(4200, SmlArray_getCommand(&sml, 2));
}

TEST(IF_GOTO_COMMAND, greater_than_line_exist)
{
    std::strcpy(argLine, "x > y goto 50");
    SymbolTable_set(
            &symbolTable,
            50,
            LINE, 
            99);
    Counters_incrementDataCounter(&counters);
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(3, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2097, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(3198, SmlArray_getCommand(&sml, 1));
    CHECK_EQUAL(4199, SmlArray_getCommand(&sml, 2));
}

TEST(IF_GOTO_COMMAND, greater_than_line_not_exist)
{
    std::strcpy(argLine, "x > y goto 50");
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(3, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2098, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(3199, SmlArray_getCommand(&sml, 1));
    CHECK_EQUAL(4100, SmlArray_getCommand(&sml, 2));
}

TEST(IF_GOTO_COMMAND, less_than_line_exist)
{
    std::strcpy(argLine, "x < y goto 50");
    SymbolTable_set(
            &symbolTable,
            50,
            LINE, 
            99);
    Counters_incrementDataCounter(&counters);
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(3, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2098, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(3197, SmlArray_getCommand(&sml, 1));
    CHECK_EQUAL(4199, SmlArray_getCommand(&sml, 2));
}

TEST(IF_GOTO_COMMAND, less_than_line_not_exist)
{
    std::strcpy(argLine, "x < y goto 50");
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
    CHECK_EQUAL(3, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2099, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(3198, SmlArray_getCommand(&sml, 1));
    CHECK_EQUAL(4100, SmlArray_getCommand(&sml, 2));
}

TEST(IF_GOTO_COMMAND, equal_zero_wrong_operand1)
{
    std::strcpy(argLine, "5 = 0 goto 50");
    CHECK_FALSE(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
}

TEST(IF_GOTO_COMMAND, equal_zero_wrong_operand2)
{
    std::strcpy(argLine, "x = 7 goto 50");
    CHECK_FALSE(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
}

TEST(IF_GOTO_COMMAND, wrong_equality_sign)
{
    std::strcpy(argLine, "x # y goto 50");
    CHECK_FALSE(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
}

TEST(IF_GOTO_COMMAND, less_than_wrong_operand2)
{
    std::strcpy(argLine, "x < 7 goto 50");
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
}

TEST(IF_GOTO_COMMAND, greater_than_wrong_operand2)
{
    std::strcpy(argLine, "x > 7 goto 50");
    CHECK(ifGotoCommandHandler(
                argLine,
                &symbolTable,
                &counters, 
                &sml,
                flags));
}
