#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

enum TypeEnum {
    TYPE_NONE = -1,
    CIRCUIT,
    AC_SOURCE,
    DC_SOURCE,
    RESISTOR,
    VOLTMETER,
    AMMETER,
    INDUCTOR,
    CAPACITOR,
    SWITCH,
    BRANCH
};

typedef struct SymbolTableCDT * SymbolTable;

SymbolTable initializeSymbolTable();
void addDeclaration(SymbolTable symbolTable, char * id, TypeEnum type, char * scopeId);
void freeSymbolTable(SymbolTable symbolTable);

#endif