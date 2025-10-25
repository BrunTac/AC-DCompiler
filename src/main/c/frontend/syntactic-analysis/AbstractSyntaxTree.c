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

void destroyElementList(ElementList * elementList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (elementList != NULL) {
		for(; elementList != NULL ; elementList = elementList->next) {
			destroyElement(elementList->current);
			ElementList * aux = elementList->next;
			free(elementList);
			elementList = aux;
		}
	}
}

void destroyComponent(Component * component) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (component != NULL) {
		destroyParameterList(component->parameterList);
		destroyIdentifier(component->id);
		free(component);
	}
}

void destroyParameter(Parameter * parameter) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (parameter != NULL) {
		switch(parameter->type) {
			case VALUE:
				free(parameter->value);
				break;
			case UNIT:
				free(parameter->unit);
				break;
			case POLARITY:
				destroyPolarity(parameter->polarity);
				break;
			case CURRENT:
				destroyCurrent(parameter->current);
				break;
		}
		free(parameter);
	}
}

void destroyParameterList(ParameterList * parameterList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (parameterList != NULL) {
		for(; parameterList != NULL ; parameterList = parameterList->next) {
			destroyParameter(parameterList->current);
			ParameterList * aux = parameterList->next;
			free(parameterList);
			parameterList = aux;
		}
	}
}

void destroyIdentifier(Identifier * identifier) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (identifier != NULL) {
		free(identifier->id);
		free(identifier);
	}
}

void destroyBranch(Branch * branch) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (branch != NULL) {
		destroyIdentifier(branch->id);
		destroyElementList(branch->elementList);
	}
}

void destroyBranchList(BranchList * branchList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (branchList != NULL) {
		for(; branchList != NULL ; branchList = branchList->next) {
			destroyBranch(branchList->current);
			BranchList * aux = branchList->next;
			free(branchList);
			branchList = aux;
		}
	}
}

void destroyParallel(Parallel * parallel) { 
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (parallel != NULL) {
		destroyBranchList(parallel->branchList);
		free(parallel);
	}
}