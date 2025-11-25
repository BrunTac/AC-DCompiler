#include "SymbolTable.h"
#include "Logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/List.h"

typedef struct SymbolTableCDT {
    List declarations;
    boolean redefinition;
    boolean differentSourceType;
} SymbolTableCDT;

typedef struct Scope {
    SourceTypeEnum * sourceType;
    char * circuitId;
} Scope;

typedef struct Declaration {
    Scope * scope;
    char * id;
    TypeEnum * type;
} Declaration;

SymbolTable initializeSymbolTable() {
    return calloc(1, sizeof(SymbolTableCDT));
}

static int declarationCmp(void * declaration1, void * declaration2){
    return strcmp(((Declaration *)declaration1)->id, ((Declaration *)declaration2)->id);
}

void addDeclaration(SymbolTable symbolTable, char * id, TypeEnum type, char * scopeId) {
    Declaration * declaration = malloc(sizeof(Declaration));
    declaration->id = id;
    declaration->type = type;
    if(type == AC_SOURCE || type == DC_SOURCE) {
        TypeEnum sourceType = getScopeSourceType(scopeId, symbolTable->declarations);
        if(sourceType != type) {
            symbolTable->differentSourceType = true;
        }
    }
    if(!addToList(symbolTable->declaration, (void *) declaration, declarationCmp)) {
        symbolTable->redefinition = true;
        free(declaration);
    }
}

void freeSymbolTable(SymbolTable symbolTable) {
    freeList(symbolTable->declarations, free);
    free(symbolTable);
}