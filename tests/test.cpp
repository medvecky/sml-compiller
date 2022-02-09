#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

 
TEST_GROUP(TEST)
{
    void setup() override
    {
    }

    void teardown() override
    {
    }
};

TEST(TEST, helloTest)
{
    CHECK_EQUAL(10, 10);
}
