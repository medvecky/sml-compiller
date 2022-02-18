#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>
extern "C"
{
#include <to_postfix_converter.h>
#include <postfix_evaluator.h>    
}

TEST_GROUP(POSTFIX_EVALUATOR)
{
    static const int STRING_LENGTH = 1024;

    char infix[STRING_LENGTH];
    PostfixEntry postfix[STRING_LENGTH]; 
    SmlArray sml;
    SymbolTable symbolTable;
    Counters counters;

    void setup() override
    {
        memset(infix, 0, sizeof(infix));
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

TEST(POSTFIX_EVALUATOR, happy_path_variables_only)
{
    //std::strcpy(infix, "( a + b ) * c - d / f\n");
    std::strcpy(infix, "( a + b ) * c - d / f\n");
    int postfixSize = convertToPostfix(infix, postfix);
    CHECK_EQUAL(9, postfixSize);
    CHECK_EQUAL(91, evaluatePostfixExpression(
                postfix,
                postfixSize, 
                &symbolTable,
                &counters,
                &sml));
    CHECK_EQUAL(12, SmlArray_getCounter(&sml));
    CHECK_EQUAL(2099, SmlArray_getCommand(&sml, 0));
    CHECK_EQUAL(3098, SmlArray_getCommand(&sml, 1));
    CHECK_EQUAL(2197, SmlArray_getCommand(&sml, 2));
    CHECK_EQUAL(2097, SmlArray_getCommand(&sml, 3));
    CHECK_EQUAL(3396, SmlArray_getCommand(&sml, 4));
    CHECK_EQUAL(2195, SmlArray_getCommand(&sml, 5));
    CHECK_EQUAL(2094, SmlArray_getCommand(&sml, 6));
    CHECK_EQUAL(3293, SmlArray_getCommand(&sml, 7));
    CHECK_EQUAL(2192, SmlArray_getCommand(&sml, 8));
    CHECK_EQUAL(2095, SmlArray_getCommand(&sml, 9));
    CHECK_EQUAL(3192, SmlArray_getCommand(&sml, 10));
    CHECK_EQUAL(2191, SmlArray_getCommand(&sml, 11));
}
