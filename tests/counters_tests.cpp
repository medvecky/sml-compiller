#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

extern "C"
{
#include <counters.h>
}

TEST_GROUP(COUNTERS)
{
    Counters counters;

    void setup() override
    {
        Counters_setDataCounter(&counters, 99);
        Counters_setInstructionCounter(&counters, 0);
    }

    void teardown() override
    {
    }
};

TEST(COUNTERS, setDataCounter_happy_path)
{
    CHECK_EQUAL(99, Counters_getDataCounter(&counters));
    CHECK(Counters_setDataCounter(&counters, 5));
    CHECK_EQUAL(5, Counters_getDataCounter(&counters));
}

TEST(COUNTERS, setDataCounter_low_limit_exceeded)
{
    CHECK_EQUAL(99, Counters_getDataCounter(&counters));
    CHECK_FALSE(Counters_setDataCounter(&counters, 100));
    CHECK_EQUAL(-1, Counters_getDataCounter(&counters));
}

TEST(COUNTERS, setDataCounter_high_limit_exceeded)
{
    CHECK_EQUAL(99, Counters_getDataCounter(&counters));
    CHECK_FALSE(Counters_setDataCounter(&counters, -1));
    CHECK_EQUAL(-1, Counters_getDataCounter(&counters));
}

TEST(COUNTERS, setDataCounter_buffer_overflow)
{
    CHECK_EQUAL(99, Counters_getDataCounter(&counters));
    Counters_setInstructionCounter(&counters, 50);
    CHECK_FALSE(Counters_setDataCounter(&counters, 50));
    CHECK_EQUAL(-1, Counters_getDataCounter(&counters));
}
// #######

TEST(COUNTERS, setInstructionCounter_happy_path)
{
    CHECK_EQUAL(0, Counters_getInstructionCounter(&counters));
    CHECK(Counters_setInstructionCounter(&counters, 5));
    CHECK_EQUAL(5, Counters_getInstructionCounter(&counters));
}

TEST(COUNTERS, setInstructionCounter_low_limit_exceeded)
{
    CHECK_EQUAL(0, Counters_getInstructionCounter(&counters));
    CHECK_FALSE(Counters_setInstructionCounter(&counters, -2));
    CHECK_EQUAL(-1, Counters_getInstructionCounter(&counters));
}

TEST(COUNTERS, setInstructionCounter_high_limit_exceeded)
{
    CHECK_EQUAL(0, Counters_getInstructionCounter(&counters));
    CHECK_FALSE(Counters_setInstructionCounter(&counters, 100));
    CHECK_EQUAL(-1, Counters_getInstructionCounter(&counters));
}

TEST(COUNTERS, setInstructionCounter_buffer_overflow)
{
    CHECK_EQUAL(0, Counters_getInstructionCounter(&counters));
    CHECK(Counters_setDataCounter(&counters, 78));
    CHECK_FALSE(Counters_setInstructionCounter(&counters, 78));
    CHECK_EQUAL(-1, Counters_getInstructionCounter(&counters));
}

TEST(COUNTERS, incrementInstructionCounter_happy_path)
{
    CHECK_EQUAL(0, Counters_getInstructionCounter(&counters));
    CHECK(Counters_incrementInstructionCounter(&counters));
    CHECK_EQUAL(1, Counters_getInstructionCounter(&counters));
}

TEST(COUNTERS, incrementInstructionCounter_limit_exceeded)
{
    CHECK(Counters_setInstructionCounter(&counters, 98));
    CHECK_FALSE(Counters_incrementInstructionCounter(&counters));
    CHECK_EQUAL(-1, Counters_getInstructionCounter(&counters));
}

TEST(COUNTERS, incrementDataCounter_happy_path)
{
    CHECK_EQUAL(99, Counters_getDataCounter(&counters));
    CHECK(Counters_incrementDataCounter(&counters));
    CHECK_EQUAL(98, Counters_getDataCounter(&counters));
}

TEST(COUNTERS, incrementDataCounter_limit_exceeded)
{
    CHECK(Counters_setInstructionCounter(&counters, 98));
    CHECK_FALSE(Counters_incrementDataCounter(&counters));
    CHECK_EQUAL(-1, Counters_getDataCounter(&counters));
}
