#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

extern "C"
{
#include <symbol_table.h>
}

TEST_GROUP(SYMBOL_TABLE)
{
    SymbolTable symbolTable;

    void setup() override
    {
        symbolTable.entryCounter = 0;
        memset(symbolTable.entries, 0, sizeof(symbolTable.entries));        
    }

    void teardown() override
    {
    }
};

TEST(SYMBOL_TABLE, set_entry_happy_path)
{
    CHECK_EQUAL(0, SymbolTable_getEntryCount(&symbolTable));
    CHECK(SymbolTable_set(&symbolTable, 10, CONSTANT, 50));
    CHECK_EQUAL(1, SymbolTable_getEntryCount(&symbolTable));
    TableEntry * result = SymbolTable_getEntry(&symbolTable,0);
    CHECK_EQUAL(10, result->symbol);
    CHECK_EQUAL(CONSTANT, result->type);
    CHECK_EQUAL(50, result->location);
}

TEST(SYMBOL_TABLE, set_entry_overflow)
{
    for (size_t counter = 0; counter < 100; counter++)
    {
        CHECK(SymbolTable_set(&symbolTable, 10, CONSTANT, 50));
    }
    CHECK_EQUAL(100, SymbolTable_getEntryCount(&symbolTable));
    CHECK_FALSE(SymbolTable_set(&symbolTable, 10, CONSTANT, 50));
    CHECK_EQUAL(100, SymbolTable_getEntryCount(&symbolTable));
}

TEST(SYMBOL_TABLE, find_location_exist)
{
    for (size_t counter = 0; counter < 50; counter++)
    {
        CHECK(SymbolTable_set(&symbolTable, 10, CONSTANT, 50));
    }
    
    CHECK(SymbolTable_set(&symbolTable, 'a', VARIABLE, 33));
    
    for (size_t counter = 51; counter < 100; counter++)
    {
        CHECK(SymbolTable_set(&symbolTable, 10, CONSTANT, 50));
    }
    
    CHECK_EQUAL(33, SymbolTable_findLocation(&symbolTable, 'a', VARIABLE));
}

TEST(SYMBOL_TABLE, find_location_not_exist)
{
    for (size_t counter = 0; counter < 50; counter++)
    {
        CHECK(SymbolTable_set(&symbolTable, 10, CONSTANT, 50));
    }
    
    CHECK(SymbolTable_set(&symbolTable, 'c', VARIABLE, 33));
    
    for (size_t counter = 51; counter < 100; counter++)
    {
        CHECK(SymbolTable_set(&symbolTable, 10, CONSTANT, 50));
    }
    
    CHECK_EQUAL(-1, SymbolTable_findLocation(&symbolTable, 'a', VARIABLE));
}
