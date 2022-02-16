#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

extern "C"
{
#include <sml_array.h>
}

TEST_GROUP(SML_ARRAY)
{
    SmlArray smlArray;
    void setup() override
    {
        smlArray.commandCounter = 0;
        memset(smlArray.commads, 0, sizeof(smlArray.commads));        
    }

    void teardown() override
    {
    }
};

TEST(SML_ARRAY, add_command_happy_path)
{
    CHECK_EQUAL(0, SmlArray_getCounter(&smlArray));
    CHECK(SmlArray_addCommand(&smlArray, 5555));
    CHECK_EQUAL(1, SmlArray_getCounter(&smlArray));
    CHECK_EQUAL(5555, SmlArray_getCommand(&smlArray, 0));
    CHECK_EQUAL(-1, SmlArray_getCommand(&smlArray, 1));
}

TEST(SML_ARRAY, add_command_overflow)
{
    for (size_t index = 0; index < 100; index++)
        CHECK(SmlArray_addCommand(&smlArray, 5555));
    CHECK_EQUAL(100, SmlArray_getCounter(&smlArray));
    CHECK_FALSE(SmlArray_addCommand(&smlArray, 5555));
}

TEST(SML_ARRAY, edit_command)
{
    CHECK_EQUAL(0, SmlArray_getCounter(&smlArray));
    CHECK(SmlArray_addCommand(&smlArray, 5555));
    CHECK_FALSE(SmlArray_editCommand(&smlArray, 1, 7777));
    CHECK(SmlArray_editCommand(&smlArray, 0, 7777));
    CHECK_EQUAL(7777, SmlArray_getCommand(&smlArray, 0));
    

} 
