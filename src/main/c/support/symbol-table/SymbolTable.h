#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

typedef enum {
    TYPE_NONE = -1,
    TYPE_CIRCUIT,
    TYPE_AC_SOURCE,
    TYPE_DC_SOURCE,
    TYPE_RESISTOR,
    TYPE_VOLTMETER,
    TYPE_AMMETER,
    TYPE_INDUCTOR,
    TYPE_CAPACITOR,
    TYPE_SWITCH,
    TYPE_BRANCH
} TypeEnum;

typedef struct SymbolTableCDT * SymbolTable;

SymbolTable initializeSymbolTable();
void addDeclaration(SymbolTable symbolTable, const char * id, TypeEnum type, const char * scopeId);
void freeSymbolTable(SymbolTable symbolTable);

#endif