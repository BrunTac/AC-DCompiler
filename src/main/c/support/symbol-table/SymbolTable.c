#include "SymbolTable.h"
#include "Logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/List.h"

typedef struct SymbolTableCDT {
    List declarations;
    boolean redefinition;
} SymbolTableCDT;

typedef struct Declaration {
    char * id;
    TypeEnum * type;
    char * branchId;
} Declaration;

SymbolTable initializeSymbolTable() {
    return calloc(1, sizeof(SymbolTableCDT));
}

static int declarationCmp(void * declaration1, void * declaration2){
    return strcmp(((Declaration *)declaration1)->id, ((Declaration *)declaration1)->id);
}

void addDeclaration(SymbolTable symbolTable, char * id, TypeEnum * type, char * branchId) {
    int added;
    Declaration * declaration = malloc(sizeof(Declaration));
    declaration->id = id;
    declaration->type = type;
    declaration->branchId = branchId;
    if(!addToList(symbolTable->declaration, (void *) declaration, declarationCmp)){
        symbolTable->redefinition = 1;
        free(declaration);
    }
}

void freeSymbolTable(SymbolTable symbolTable) {
    freeList(symbolTable->declarations, free);
    free(symbolTable);
}