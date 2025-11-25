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
    char * scopeId;
    char * id;
    TypeEnum type;
} Declaration;

SymbolTable initializeSymbolTable() {
    return calloc(1, sizeof(SymbolTableCDT));
}

static int declarationCmp(void * declaration1, void * declaration2){
    int ans = strcmp(((Declaration *)declaration1)->scopeId, ((Declaration *)declaration2)->scopeId);
    if(ans == 0){
        ans = strcmp(((Declaration *)declaration1)->id, ((Declaration *)declaration2)->id);
    }
    return ans;
}

void addDeclaration(SymbolTable symbolTable, char * id, TypeEnum type, char * scopeId) {
    Declaration * declaration = malloc(sizeof(Declaration));
    declaration->scopeId = scopeId;
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

TypeEnum getScopeSourceType(char * scopeId, List declarations) {
    if (list == NULL) {
        return TYPE_NONE;
    }
    Node * curr = list;
    do {
        Declaration * currDeclaration = ((Declaration *) curr->data)->type;
        if((strcmp(currDeclaration->scopeId, scopeId) == 0) && (currDeclaration->type == AC_SOURCE || currDeclaration->type == AC_SOURCE)) {
            return currDeclaration->type;
        }
        curr = curr->next;
    } while (curr != NULL);
    
    return TYPE_NONE;
}