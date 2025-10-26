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
		CircuitList * aux;
		while(circuitList != NULL) {
			aux = circuitList->next;
			destroyCircuit(circuitList->current);
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
		ElementList * aux;
		while(elementList != NULL) {
			aux = elementList->next;
			destroyElement(elementList->current);
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
			case UNIT_MULTIPLIER:
				break;
			case POLARITY:
				destroyPolarity(parameter->polarity);
				break;
			case RESISTOR_TYPE:
				break;
			case SWITCH_STATE:
				break;
		}
		free(parameter);
	}
}

void destroyParameterList(ParameterList * parameterList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (parameterList != NULL) {
		ParameterList *aux;
		while (parameterList != NULL) {
			aux = parameterList->next;         
			destroyParameter(parameterList->current); 
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
		free(branch);
	}
}

void destroyBranchList(BranchList * branchList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (branchList != NULL) {
		BranchList * aux;
		while(branchList != NULL) {
			aux = branchList->next;
			destroyBranch(branchList->current);
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

void destroyPolarity(Polarity * polarity) { 
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (polarity != NULL) {
		free(polarity);
	}
}
