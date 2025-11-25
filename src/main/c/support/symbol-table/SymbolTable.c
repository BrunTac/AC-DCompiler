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

typedef struct Declaration {
    const char * scopeId;
    const char * id;
    TypeEnum type;
} Declaration;

SymbolTable initializeSymbolTable() {
    return calloc(1, sizeof(SymbolTableCDT));
}

static int declarationCmp(void * declaration1, void * declaration2){
    Declaration * d1 = (Declaration *) declaration1;
    Declaration * d2 = (Declaration *) declaration2;

    int ans = strcmp(d1->scopeId, d2->scopeId);
    if (ans == 0) {
        ans = strcmp(d1->id, d2->id);
    }
    return ans;
}

void addDeclaration(SymbolTable symbolTable, const char * id, TypeEnum type, const char * scopeId) {
    Declaration * declaration = malloc(sizeof(Declaration));
    declaration->scopeId = scopeId;
    declaration->id = id;
    declaration->type = type;
    if(type == TYPE_AC_SOURCE || type == TYPE_DC_SOURCE) {
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

TypeEnum getScopeSourceType(const char * scopeId, List declarations) {
    if (list == NULL) {
        return TYPE_NONE;
    }
    Node * curr = list;
    do {
        Declaration * currDeclaration = ((Declaration *) curr->data)->type;
        if((strcmp(currDeclaration->scopeId, scopeId) == 0) && (currDeclaration->type == TYPE_AC_SOURCE || currDeclaration->type == TYPE_DC_SOURCE)) {
            return currDeclaration->type;
        }
        curr = curr->next;
    } while (curr != NULL);
    
    return TYPE_NONE;
}