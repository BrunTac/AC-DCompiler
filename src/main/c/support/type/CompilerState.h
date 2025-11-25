#ifndef COMPILER_STATE_HEADER
#define COMPILER_STATE_HEADER

#include "../symbol-table/SymbolTable.h"

/**
 * The global state of the compiler. Should transport every data structure
 * needed across the different phases of a compilation.
 */
typedef struct {
	void * abstractSyntaxtTree;
	const char * currentScopeId;
	SymbolTable symbolTable;
} CompilerState;

#endif