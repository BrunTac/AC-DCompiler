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

Circuit * CircuitSemanticAction(Identifier identifier, ElementList elementList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Circuit * circuit = calloc(1, sizeof(Circuit));
	circuit->identifier = identifier;
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

Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Factor * ExpressionFactorSemanticAction(Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
}
