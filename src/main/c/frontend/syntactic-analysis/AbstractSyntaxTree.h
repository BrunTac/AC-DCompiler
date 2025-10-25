#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../support/logging/Logger.h"
#include "../../support/type/ModuleDestructor.h"
#include <stdlib.h>

/** Initialize module's internal state. */
ModuleDestructor initializeAbstractSyntaxTreeModule();

/**
 * This type definitions allows self-referencing types (e.g., an expression
 * that is made of another expressions, such as talking about you in 3rd
 * person, but without the madness).
 */

typedef enum Polarity Polarity;
typedef enum Current Current;
typedef enum Unit Unit;

typedef enum ComponentType ComponentType;
typedef enum ElementType ElementType;
typedef enum ParameterType ParameterType;

typedef struct Program Program;
typedef struct Circuit Circuit;
typedef struct CircuitList CircuitList;
typedef struct Element Element;
typedef struct ElementList ElementList;
typedef struct Component Component;
typedef struct Parameter Parameter;
typedef struct ParameterList ParameterList;
typedef struct Identifier Identifier;
typedef struct Branch Branch;
typedef struct BranchList BranchList;
typedef struct Parallel Parallel;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum Polarity {
	POSITIVE_FIRST,
	NEGATIVE_FIRST
};

enum Current {
	DIRECT,
	ALTERNATING
};

enum Unit {
	GIGA,
	MEGA,
	KILO,
	BASE,
	MILLI,
	MICRO,
	NANO
};

enum ComponentType {
	COMPONENT_AC_SOURCE,
	COMPONENT_DC_SOURCE,
	COMPONENT_RESISTANCE,
	COMPONENT_VOLTMETER,
	COMPONENT_AMPEREMETER,
	COMPONENT_INDUCTANCE,
	COMPONENT_CAPACITOR,
	COMPONENT_SWITCH
};

enum ElementType {
	ELEMENT_COMPONENT,
	ELEMENT_PARALLEL
};

enum ParameterType {
	VALUE,
	UNIT,
	POLARITY,
	CURRENT
};

struct Program {
	CircuitList * circuitList;
};

struct Circuit {
	Identifier * id;
	ElementList * elementList;
};

struct CircuitList {
	Circuit * current;
	CircuitList * next;
};

struct Element {
	union {
		Component * component;
		Parallel * parallel;
	};
	ElementType type;
};

struct ElementList {
	Element * current;
	ElementList * next;
};

struct Component {
	ComponentType type;
	ParameterList * parameterList;
	Identifier * id;
};

struct Parameter {
	union {
		const char ** value;
		Unit * unit;
		Polarity * polarity;
		Current * current;
	};
	ParameterType type;
};

struct ParameterList { 
	Parameter * current;
	ParameterList * next;
};

struct Identifier {
	const char ** id;
};

struct Branch {
	Identifier * id;
	ElementList * elementList;
};

struct BranchList {
	Branch * current;
	BranchList * next;
};

struct Parallel {
	BranchList * branchList;
};


/**
 * Node recursive super-duper-trambolik-destructors.
 */

void destroyProgram(Program*);
void destroyCircuit(Circuit*);
void destroyCircuitList(CircuitList*);
void destroyElement(Element*);
void destroyElementList(ElementList*);
void destroyParallel(Parallel*);
void destroyBranch(Branch*);
void destroyBranchList(BranchList*);
void destroyComponent(Component*);
void destroyParameter(Parameter*);
void destroyParameterList(ParameterList*);
void destroyPolarity(Polarity*);
void destroyCurrent(Current*);
void destroyIdentifier(Identifier*);

#endif
