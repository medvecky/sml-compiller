#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

extern "C"
{
#include <to_postfix_converter.h>
}

TEST_GROUP(TO_POSTFIX_CONVERTER)
{
    static const int STRING_LENGTH = 1024;

    char infix[STRING_LENGTH];
    PostfixEntry postfix[STRING_LENGTH]; 

    void setup() override
    {
        memset(infix, 0, sizeof(infix));
        memset(postfix, 0, sizeof(postfix));
    }

    void teardown() override
    {
    }
};

TEST(TO_POSTFIX_CONVERTER, correct_string)
{
    std::strcpy(infix, "( 60 + a ) * b - c / 4\n");
    int result = convertToPostfix(infix, postfix);
    CHECK_EQUAL(9, result);
    CHECK_EQUAL(60, postfix[0].item);
    CHECK_EQUAL(CONSTANT, postfix[0].type);
    CHECK_EQUAL('a', postfix[1].item);
    CHECK_EQUAL(VARIABLE, postfix[1].type);
    CHECK_EQUAL('+', postfix[2].item);
    CHECK_EQUAL(OPERATOR, postfix[2].type);
    CHECK_EQUAL('b', postfix[3].item);
    CHECK_EQUAL(VARIABLE, postfix[3].type);
    CHECK_EQUAL('*', postfix[4].item);
    CHECK_EQUAL(OPERATOR, postfix[4].type);
    CHECK_EQUAL('c', postfix[5].item);
    CHECK_EQUAL(VARIABLE, postfix[5].type);
    CHECK_EQUAL(4, postfix[6].item);
    CHECK_EQUAL(CONSTANT, postfix[6].type);
    CHECK_EQUAL('/', postfix[7].item);
    CHECK_EQUAL(OPERATOR, postfix[7].type);
    CHECK_EQUAL('-', postfix[8].item);
}

TEST(TO_POSTFIX_CONVERTER, bad_token)
{
    std::strcpy(infix, "(60 + a) * b - c / 4\n");
    int result = convertToPostfix(infix, postfix);
    CHECK_EQUAL(-1, result);
}

TEST(TO_POSTFIX_CONVERTER, bad_number)
{
    std::strcpy(infix, "( 6.0 + a ) * b - c / 4\n");
    int result = convertToPostfix(infix, postfix);
    CHECK_EQUAL(-1, result);
}

TEST(TO_POSTFIX_CONVERTER, bad_variable)
{
    std::strcpy(infix, "( 6 + an ) * b - c / 4\n");
    int result = convertToPostfix(infix, postfix);
    CHECK_EQUAL(-1, result);
}

TEST(TO_POSTFIX_CONVERTER, bad_operator)
{
    std::strcpy(infix, "( 6 + a ) % b - c / 4\n");
    int result = convertToPostfix(infix, postfix);
    CHECK_EQUAL(-1, result);
}
