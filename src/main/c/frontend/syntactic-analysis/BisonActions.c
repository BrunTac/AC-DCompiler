#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static CompilerState * _compilerState = NULL;
static Logger * _logger = NULL;

/** Shutdown module's internal state. */
void _shutdownBisonActionsModule() {
	if (_logger != NULL) {
		logDebugging(_logger, "Destroying module: BisonActions...");
		destroyLogger(_logger);
		_logger = NULL;
	}
	_compilerState = NULL;
}

ModuleDestructor initializeBisonActionsModule(CompilerState * compilerState) {
	_compilerState = compilerState;
	_logger = createLogger("BisonActions");
	return _shutdownBisonActionsModule;
}

/* IMPORTED FUNCTIONS */

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

Program * ProgramSemanticAction(CircuitList * circuitList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->circuitList = circuitList;
	_compilerState->abstractSyntaxtTree = program;
	return program;
}

CircuitList * NewCircuitListSemanticAction(Circuit * circuit) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CircuitList * circuitList = calloc(1, sizeof(CircuitList));
	circuitList->current = circuit;
	circuitList->next = NULL;
	return circuitList;
}

CircuitList * AppendCircuitSemanticAction(CircuitList * circuitList, Circuit * circuit) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CircuitList * newNode = calloc(1, sizeof(CircuitList));
	newNode->current = circuit;
	newNode->next = NULL;

	CircuitList * aux = circuitList;
	while(aux->next != NULL){
		aux = aux->next;
	}
	aux->next = newNode;
	return circuitList;
}

Circuit * CircuitSemanticAction(Identifier * identifier, ElementList * elementList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Circuit * circuit = calloc(1, sizeof(Circuit));
	circuit->id = identifier;
	circuit->elementList = elementList;
	return circuit;
}

ElementList * EmptyElementListSemanticAction() {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ElementList * elementList = calloc(1, sizeof(ElementList));
	elementList->current = NULL;
	elementList->next = NULL;
	return elementList;
}

ElementList * NewElementListSemanticAction(Element * element) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ElementList * elementList = calloc(1, sizeof(ElementList));
	elementList->current = element;
	elementList->next = NULL;
	return elementList;
}

ElementList * AppendElementSemanticAction(ElementList * elementList, Element * element) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ElementList * newNode = calloc(1, sizeof(ElementList));
	newNode->current = element;
	newNode->next = NULL;

	ElementList * aux = elementList;
	while(aux->next != NULL){
		aux = aux->next;
	}
	aux->next = newNode;
	return elementList;
}

Element * ComponentElementSemanticAction(Component * component) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * element = calloc(1, sizeof(Element));
	element->component = component;
	element->type = ELEMENT_COMPONENT;
	return element;
}

Element * ParallelElementSemanticAction(Parallel * parallel) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * element = calloc(1, sizeof(Element));
	element->parallel = parallel;
	element->type = ELEMENT_PARALLEL;
	return element;
}

Parallel * ParallelSemanticAction(BranchList * branchList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Parallel * parallel = calloc(1, sizeof(Parallel));
	parallel->branchList = branchList;
	return parallel;
}

BranchList * NewBranchListSemanticAction(Branch * leftBranch, Branch * rightBranch) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BranchList * branchList = calloc(1, sizeof(BranchList));
	BranchList * secondNode = calloc(1, sizeof(BranchList));
	branchList->current = leftBranch;
	branchList->next = secondNode;
	secondNode->current = rightBranch;
	secondNode->next = NULL;
	return branchList;
}

BranchList * AppendBranchSemanticAction(BranchList * branchList, Branch * branch) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BranchList * newNode = calloc(1, sizeof(BranchList));
	newNode->current = branch;
	newNode->next = NULL;

	BranchList * aux = branchList;
	while(aux->next != NULL){
		aux = aux->next;
	}
	aux->next = newNode;
	return branchList;
}

Branch * BranchSemanticAction(Identifier * identifier, ElementList * elementList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Branch * branch = calloc(1, sizeof(Branch));
	branch->id = identifier;
	branch->elementList = elementList;
	return branch;
}

Component * ACSourceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Component * component = calloc(1, sizeof(Component));
	component->type = COMPONENT_AC_SOURCE;
	component->id = identifier;
	component->parameterList = parameterList;
	return component;
}

Component * DCSourceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Component * component = calloc(1, sizeof(Component));
	component->type = COMPONENT_DC_SOURCE;
	component->id = identifier;
	component->parameterList = parameterList;
	return component;
}

Component * ResistanceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Component * component = calloc(1, sizeof(Component));
	component->type = COMPONENT_RESISTANCE;
	component->id = identifier;
	component->parameterList = parameterList;
	return component;
}

Component * VoltmeterComponentSemanticAction(Identifier * identifier, ParameterList * parameterList){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Component * component = calloc(1, sizeof(Component));
	component->type = COMPONENT_VOLTMETER;
	component->id = identifier;
	component->parameterList = parameterList;
	return component;
}

Component * AmperemeterComponentSemanticAction(Identifier * identifier, ParameterList * parameterList){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Component * component = calloc(1, sizeof(Component));
	component->type = COMPONENT_AMPEREMETER;
	component->id = identifier;
	component->parameterList = parameterList;
	return component;
}

Component * InductanceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Component * component = calloc(1, sizeof(Component));
	component->type = COMPONENT_INDUCTANCE;
	component->id = identifier;
	component->parameterList = parameterList;
	return component;
}

Component * CapacitorComponentSemanticAction(Identifier * identifier, ParameterList * parameterList){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Component * component = calloc(1, sizeof(Component));
	component->type = COMPONENT_CAPACITOR;
	component->id = identifier;
	component->parameterList = parameterList;
	return component;
}

Component * SwitchComponentSemanticAction(Identifier * identifier, ParameterList * parameterList){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Component * component = calloc(1, sizeof(Component));
	component->type = COMPONENT_SWITCH;
	component->id = identifier;
	component->parameterList = parameterList;
	return component;
}

ParameterList * EmptyParameterListSemanticAction() {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ParameterList * parameterList = calloc(1, sizeof(ParameterList));
	parameterList->current = NULL;
	parameterList->next = NULL;
	return parameterList;
}

ParameterList * NewParameterListSemanticAction(Parameter * parameter) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ParameterList * parameterList = calloc(1, sizeof(ParameterList));
	parameterList->current = parameter;
	parameterList->next = NULL;
	return parameterList;
}

ParameterList * AppendParameterSemanticAction(ParameterList * parameterList, Parameter * parameter) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ParameterList * newNode = calloc(1, sizeof(ParameterList));
	newNode->current = parameter;
	newNode->next = NULL;

	ParameterList * aux = parameterList;
	while(aux->next != NULL){
		aux = aux->next;
	}
	aux->next = newNode;
	return parameterList;
}

Parameter * ParameterValueSemanticAction(const char ** value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Parameter * parameter = calloc(1, sizeof(Parameter));
	parameter->value = value;
	parameter->type = VALUE;
	return parameter;
}

Parameter * ParameterUnitSemanticAction(Unit * unit) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Parameter * parameter = calloc(1, sizeof(Parameter));
	parameter->unit = unit;
	parameter->type = UNIT;
	return parameter;
}

Parameter * ParameterPolaritySemanticAction(Polarity * polarity) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Parameter * parameter = calloc(1, sizeof(Parameter));
	parameter->polarity = polarity;
	parameter->type = POLARITY;
	return parameter;
}

Parameter * ParameterCurrentSemanticAction(Current * current) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Parameter * parameter = calloc(1, sizeof(Parameter));
	parameter->current = current;
	parameter->type = CURRENT;
	return parameter;
}

Identifier * IdentifierSemanticAction(const char ** id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Identifier * identifier = calloc(1, sizeof(Identifier));
	identifier->id = id;
	return identifier;
}