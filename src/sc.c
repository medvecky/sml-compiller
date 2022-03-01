#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "modules/counters.h"
#include "modules/sml_array.h"
#include "modules/symbol_table.h"
#include "modules/postfix_evaluator.h"
#include "modules/commands.h"
#include "modules/to_postfix_converter.h"
#include "modules/let_command_hadnler.h"

#define STRING_LENGTH   1024

int handleArguments(int argc, char ** argv, char ** outputFileName);

int main(int argc, char ** argv)
{
    char * outputFileName = NULL;

    SymbolTable symbolTable;
    symbolTable.entryCounter = 0;

    Counters counters;
    counters.dataCounter = 99;
    counters.instructionCounter = 0;

    SmlArray sml;
    sml.commandCounter = 0;

    PostfixEntry postfix[STRING_LENGTH];
    
    if (handleArguments(argc, argv, &outputFileName) == EXIT_FAILURE)
        return EXIT_FAILURE;

    FILE * sourceFile = fopen(argv[1], "r");

    if (sourceFile == NULL)
    {
        printf("Can't open source file: %s", argv[1]);
        puts("USAGE: sc simple_file_name [-o sml_file_name]");
        return EXIT_FAILURE;
    } // end if

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, sourceFile)) != -1) 
    {
        size_t lineLength = strlen(line);
        char * lineForTekenization = calloc(lineLength, sizeof(char));
        strncpy(lineForTekenization, line, lineLength);
        char * token = strtok(lineForTekenization, " ");
        int lineNumber = 0;
        char * command = NULL;
        size_t commandPartLength = 0;
        
        if (token != NULL)
        {
            commandPartLength += strlen(token);
            lineNumber = atoi(token);
        } // end if

        if ((token = strtok(NULL, " ")) != NULL)
        {
            command = token;
            commandPartLength += strlen(command);
        } // end if

        commandPartLength += 2;

        if (strncmp(command, "rem", STRING_LENGTH) == 0)
        {
            if (SymbolTable_findLocation(&symbolTable, lineNumber, LINE) == -1)
            {
                if (!SymbolTable_set(
                        &symbolTable,
                        lineNumber, 
                        LINE,
                        Counters_getInstructionCounter(&counters)))
                    return EXIT_FAILURE;
            } // end if not in symbol table
        } // end if rem
        else if (strncmp(command, "let", STRING_LENGTH) == 0)
        {
            if (!SymbolTable_set(
                &symbolTable,
                lineNumber, 
                LINE,
                Counters_getInstructionCounter(&counters)))
                return EXIT_FAILURE;

            char * argLine = line + commandPartLength;

            if (!letCommandHandler(argLine, 
                        &symbolTable,
                        &counters, 
                        postfix,
                        &sml))
                return EXIT_FAILURE;
        } // end else if let
        else
        {
            printf("Incorrect command %s in string %d\n", command, lineNumber);
            //return EXIT_FAILURE;
        } // end else
        free(lineForTekenization);
    } // end while

    fclose(sourceFile);
    if (line)
        free(line);
    
    puts("SymbolTable:");
    for (size_t counter = 0; counter < SymbolTable_getEntryCount(&symbolTable); counter++)
    {
        TableEntry * entry = SymbolTable_getEntry(&symbolTable, counter); 
        printf("%zu: Symbol: %d | %c, type: %d, location: %zu\n", 
                counter,
                entry->symbol,
                entry->symbol, 
                entry->type,
                entry->location);
    } // end for show symbolTable
    
    puts("Sml:");
    for (size_t counter = 0; counter < SmlArray_getCounter(&sml); counter++)
    {
        printf("%zu\t%d\n", counter, SmlArray_getCommand(&sml, counter));
    } // end for show symbolTable

    printf("Data counter: %d, Instruction counter: %d\n",
            Counters_getDataCounter(&counters),
            Counters_getInstructionCounter(&counters));
    puts("End of program.");
    return EXIT_SUCCESS;
} // end main

int handleArguments(int argc, char ** argv, char ** outputFileName)
{
    if (argc < 2)
    {
        puts("USAGE: sc simple_file_name [-o sml_file_name]");
        return EXIT_FAILURE;
    } // end if

    int option;
    while ((option = getopt(argc, argv, "o:")) != -1)
    {
        switch (option)
        {
            case 'o':
                *outputFileName = optarg;
                break;
            case '?':
                if (optopt == 'o')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, 
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return EXIT_FAILURE;
        } // end switch
    } // end while

    return EXIT_SUCCESS;
} // end function handleArguments 


