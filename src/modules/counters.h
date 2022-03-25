#ifndef _COUNTERS_H_
#define _COUNTERS_H_

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define MEMORY_LIMIT    99

struct counters
{
    size_t instructionCounter;
    size_t dataCounter;
};

typedef struct counters Counters;

bool Counters_setInstructionCounter(Counters * counters, size_t value);
bool Counters_setDataCounter(Counters * counters, size_t value);
int Counters_getInstructionCounter(Counters * counters);
int Counters_getDataCounter(Counters * counters);
bool Counters_incrementDataCounter(Counters * counters);
bool Counters_incrementInstructionCounter(Counters * counters);

#endif
