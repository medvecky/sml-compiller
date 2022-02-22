#include "symbol_table.h"
#include <stddef.h>

bool SymbolTable_set(
        SymbolTable * symbolTable,
        int symbol,
        TableEntryType type,
        size_t location)
{
    size_t index;

    if ((index = symbolTable->entryCounter) >= SYMBOL_TABLE_SIZE)
        return false;

    symbolTable->entries[index].symbol = symbol; 
    symbolTable->entries[index].type = type;
    symbolTable->entries[index].location = location;

    symbolTable->entryCounter++;

    return true;
} // end function SymbolTable_set

int SymbolTable_findLocation(
        SymbolTable * symbolTable,
        int symbol,
        TableEntryType type)
{
    size_t numberOfEntries = symbolTable->entryCounter;
    for (size_t index = 0; index < numberOfEntries; index++)
    {
        TableEntry entry = symbolTable->entries[index];
        if (entry.symbol == symbol && entry.type == type)
            return entry.location;
    } // end for find loop
    return -1;
} // end function SymbolTable_findLocation

TableEntry * SymbolTable_getEntry(SymbolTable * symbolTable, size_t index)
{
    return &symbolTable->entries[index];
} // end function SymbolTable_getEntry

size_t SymbolTable_getEntryCount(SymbolTable * symbolTable)
{
    return symbolTable->entryCounter;    
} // end function SymbolTable_getEntryCount
