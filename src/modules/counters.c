#include "counters.h"

static bool isValid(Counters * counters);

bool Counters_setInstructionCounter(Counters * counters, size_t value)
{
    counters->instructionCounter = value;
    return isValid(counters);
} // end function Counters_setInstructionCounter

bool Counters_setDataCounter(Counters * counters, size_t value)
{
    counters->dataCounter = value;
    return isValid(counters);
} // end function Counters_setDataCounter

int Counters_getInstructionCounter(Counters * counters)
{
    if (isValid(counters))
    {
        return counters->instructionCounter;
    } // end if

    return -1;
} // end function Counters_getInstructionCounter

int Counters_getDataCounter(Counters * counters)
{
    if (isValid(counters))
    {
        return counters->dataCounter;
    } // end if

    return -1;
} // end function Counters_getInstructionCounter

bool Counters_incrementDataCounter(Counters * counters)
{
    counters->dataCounter--;
    return isValid(counters);
} // end function Counters_incrementDataCounter

bool Counters_incrementInstructionCounter(Counters * counters)
{
    counters->instructionCounter++;
    return isValid(counters);
} // end function Counters_incrementInstructionCounter

static bool isValid(Counters * counters)
{
    if (counters->instructionCounter < 0 || counters->instructionCounter > MEMORY_LIMIT)
        return false;
    if (counters->dataCounter < 0 || counters->dataCounter > MEMORY_LIMIT)
        return false;
    if (counters->instructionCounter >= counters->dataCounter)
        return false;
    return true;
} // end function isValid
