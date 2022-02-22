#ifndef _SML_ARRAY_H
#define _SML_ARRAY_H

#include <stdio.h>
#include <stdbool.h>

#define SML_ARRAY_SIZE  100

struct smlArray
{
    int commads[SML_ARRAY_SIZE];
    size_t commandCounter;
};

typedef struct smlArray SmlArray;

size_t SmlArray_getCounter(SmlArray * smlArray);
bool SmlArray_addCommand(SmlArray * smlArray, int command);
bool SmlArray_editCommand(SmlArray * smlArray, size_t commandNumber, int command);
int SmlArray_getCommand(SmlArray * smlArray, size_t commandNumber);

#endif
