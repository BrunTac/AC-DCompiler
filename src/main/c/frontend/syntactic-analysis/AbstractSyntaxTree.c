#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

/** Shutdown module's internal state. */
void _shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		logDebugging(_logger, "Destroying module: AbstractSyntaxTree...");
		destroyLogger(_logger);
		_logger = NULL;
	}
}

ModuleDestructor initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntaxTree");
	return _shutdownAbstractSyntaxTreeModule;
}

/* PUBLIC FUNCTIONS */

void destroyProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		destroyCircuitList(program->circuitList);
		free(program);
	}
}

void destroyCircuit(Circuit * circuit) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (circuit != NULL) {
		destroyIdentifier(circuit->id);
		destroyElementList(circuit->elementList);
		free(circuit);
	}
}

void destroyCircuitList(CircuitList * circuitList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (circuitList != NULL) {
		for(; circuitList != NULL ; circuitList = circuitList->next) {
			destroyCircuit(circuitList->current);
			CircuitList * aux = circuitList->next;
			free(circuitList);
			circuitList = aux;
		}
	}
}

void destroyElement(Element * element) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (element != NULL) {
		switch(element->type) {
			case ELEMENT_COMPONENT:
				destroyComponent(element->component);
				break;
			case ELEMENT_PARALLEL:
				destroyParallel(element->parallel);
				break;
		}
		free(element);
	}
}
