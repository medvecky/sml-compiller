#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define SYMBOL_TABLE_SIZE       100

enum tableEntryType {CONSTANT, LINE, VARIABLE};
typedef enum tableEntryType TableEntryType;

struct tableEntry
{
    int symbol;
    TableEntryType type;
    size_t location;
};
typedef struct tableEntry TableEntry;

struct symbolTable
{
    TableEntry entries[SYMBOL_TABLE_SIZE];
    size_t entryCounter;
};
typedef struct symbolTable SymbolTable;

bool SymbolTable_set(
        SymbolTable * symbolTable,
        int symbol, TableEntryType type,
        size_t location);
int SymbolTable_findLocation(
        SymbolTable * symbolTable,
        int symbol,
        TableEntryType type);
TableEntry * SymbolTable_getEntry(SymbolTable * symbolTable, size_t index);
size_t SymbolTable_getEntryCount(SymbolTable * symbolTable);

#endif
