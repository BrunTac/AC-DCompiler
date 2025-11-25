#ifndef SYMBOL__TABLE
#define SYMBOL__TABLE

enum TypeEnum {
    CIRCUIT,
    AC_SOURCE,
    DC_SOURCE,
    RESISTOR,
    VOLTMETER,
    AMMETER,
    INDUCTOR,
    CAPACITOR,
    SWITCH,
    PARALLEL,
    BRANCH
};

typedef struct SymbolTableCDT * SymbolTable;

SymbolTable initializeSymbolTable();
void addDeclaration(SymbolTable symbolTable, char * id, TypeEnum * type, char * branchId);
void freeSymbolTable(SymbolTable symbolTable);

#endif